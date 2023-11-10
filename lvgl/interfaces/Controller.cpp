#include "lvgl/interfaces/Controller.hpp"
#include "infra/util/BoundedVector.hpp"
#include "infra/util/ByteRange.hpp"
#include "infra/util/MemoryRange.hpp"
#include <src/core/lv_obj.h>
#include <src/hal/lv_hal_indev.h>
#include <src/misc/lv_area.h>

namespace embedded::lvgl
{
    Controller::Controller(DriverDisplay& display, DriverInputDevice& inputDevice)
        : display(display)
        , inputDevice(inputDevice)
    {
        if (!lv_is_initialized())
            lv_init();

        DisplayInitialization();
        InputDeviceInitialization();

        tick.Start(std::chrono::milliseconds(1), []()
            {
                lv_tick_inc(1);
                lv_timer_handler_run_in_period(5);
            });
    }

    Controller::~Controller()
    {
        tick.Cancel();

        if (lvglDisplay)
            lv_disp_remove(lvglDisplay);

        if (lvglInput)
            lv_indev_delete(lvglInput);

        if (lv_is_initialized())
            lv_deinit();
    }

    void Controller::DisplayInitialization()
    {
        really_assert(display.GetBuffer1().size() % display.PixelSize() == 0);

        if (!display.GetBuffer2().empty())
            really_assert(display.GetBuffer1().size() == display.GetBuffer2().size());

        lv_disp_draw_buf_init(&lvglDrawBuffers, display.GetBuffer1().begin(), display.GetBuffer2().begin(), display.GetBuffer1().size() / display.PixelSize());
        lv_disp_drv_init(&lvglDisplayDescriptor);

        lvglDisplayDescriptor.user_data = &display;

        lvglDisplayDescriptor.hor_res = static_cast<lv_coord_t>(display.GetHorizontalResolution());
        lvglDisplayDescriptor.ver_res = static_cast<lv_coord_t>(display.GetVerticalResolution());
        lvglDisplayDescriptor.draw_buf = &lvglDrawBuffers;
        lvglDisplayDescriptor.flush_cb = &StaticLvglFlush;

#if 0
        lvglDisplayDescriptor.set_px_cb = &StaticLvglSetPixel;
        lvglDisplayDescriptor.clear_cb = &StaticLvglClear;
        lvglDisplayDescriptor.clean_dcache_cb = &StaticLvglCleanDCache;
#endif

#if 0 // If GPU is supported...
        lvglDisplayDescriptor.draw_ctx_init = &StaticLvglDrawInit;
        lvglDisplayDescriptor.draw_ctx_deinit = &StaticLvglDrawDeInit;
#endif

        lvglDisplay = lv_disp_drv_register(&lvglDisplayDescriptor);
    }

    void Controller::InputDeviceInitialization()
    {
        lv_indev_drv_init(&lvglInputDescriptor);

        lvglInputDescriptor.user_data = &inputDevice;

        lvglInputDescriptor.read_cb = &StaticLvglRead;
        lvglInputDescriptor.feedback_cb = &StaticLvglFeedback;
        lvglInputDescriptor.type = static_cast<lv_indev_type_t>(inputDevice.Type());
        lvglInputDescriptor.disp = lvglDisplay;

        lvglInput = lv_indev_drv_register(&lvglInputDescriptor);
    }

    void Controller::StaticLvglFlush(struct _lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
    {
        auto driver = reinterpret_cast<DriverDisplay*>(disp_drv->user_data);
        auto size = (area->x2 - area->x1 + 1) * (area->y2 - area->y1 + 1);

        driver->Flush(*area, infra::MemoryRange<Color>(color_p, color_p + size), [&disp_drv]()
            {
                lv_disp_flush_ready(disp_drv);
            });
    }

    void Controller::StaticLvglSetPixel(struct _lv_disp_drv_t * disp_drv, uint8_t * buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa)
    {
        auto driver = reinterpret_cast<DriverDisplay*>(disp_drv->user_data);

        driver->SetPixel(infra::MakeConstByteRange(buf), buf_w, { x, y }, color, opa);
    }

    void Controller::StaticLvglClear(struct _lv_disp_drv_t * disp_drv, uint8_t * buff, uint32_t size)
    {
        auto driver = reinterpret_cast<DriverDisplay*>(disp_drv->user_data);

        driver->Clear(infra::ConstByteRange(buff, buff + size));
    }

    void Controller::StaticLvglCleanDCache(struct _lv_disp_drv_t * disp_drv)
    {
        auto driver = reinterpret_cast<DriverDisplay*>(disp_drv->user_data);

        driver->CleanDCache();
    }

    void Controller::StaticLvglDrawInit(struct _lv_disp_drv_t *, lv_draw_ctx_t *)
    {
#if 0
        // start gpu...
#endif
    }

    void Controller::StaticLvglDrawDeInit(struct _lv_disp_drv_t *, lv_draw_ctx_t *)
    {
#if 0
        // stop gpu...
#endif
    }

    void Controller::StaticLvglRead(struct _lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
    {
#if 0
        auto driver = reinterpret_cast<DriverInputDevice*>(indev_drv->user_data);
        really_assert(driver->Type() != DriverInputDevice::InputType::none);

        auto response = driver->Read();

        data->continue_reading = response.continueReading;
        data->state = response.state == DriverInputDevice::State::pressed ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;

        if (driver->Type() == DriverInputDevice::InputType::pointer)
        {
            data->point.x = response.action.Get<Point>().x;
            data->point.y = response.action.Get<Point>().y;
        }
        else if (driver->Type() == DriverInputDevice::InputType::button)
            data->btn_id = response.action.Get<ButtonId>();
        else if (driver->Type() == DriverInputDevice::InputType::keypad)
            data->key = response.action.Get<Keypad>();
        else if (driver->Type() == DriverInputDevice::InputType::encoder)
            data->enc_diff = response.action.Get<Encoder>();
#endif
    }

    void Controller::StaticLvglFeedback(struct _lv_indev_drv_t * indev_drv, uint8_t)
    {
        auto driver = reinterpret_cast<DriverInputDevice*>(indev_drv->user_data);

        driver->Feedback();
    }
}
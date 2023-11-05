#ifndef EMBEDDED_LVGL_INTERFACES_CONTROLLER_HPP
#define EMBEDDED_LVGL_INTERFACES_CONTROLLER_HPP

#include "infra/util/ByteRange.hpp"
#include "infra/util/Function.hpp"
#include "infra/util/BoundedVector.hpp"
#include "infra/timer/Timer.hpp"
#include "infra/util/MemoryRange.hpp"
#include "infra/util/Variant.hpp"
#include "lvgl.h"
#include <sys/_stdint.h>

namespace embedded::lvgl
{
    struct Point
    {
        lv_coord_t x;
        lv_coord_t y;
    };

    using Area = lv_area_t;
    using Color = lv_color_t;

    class DriverDisplay
    {
    public:
        virtual ~DriverDisplay() = default;

        virtual std::size_t GetHorizontalResolution() = 0;
        virtual std::size_t GetVerticalResolution() = 0;

        virtual infra::MemoryRange<Color> GetBuffer1() = 0;
        virtual infra::MemoryRange<Color> GetBuffer2() = 0;
        virtual std::size_t PixelSize() = 0;

        virtual void Flush(Area area, infra::MemoryRange<Color> color, const infra::Function<void()>& onDone) = 0;
        virtual void SetPixel(infra::ConstByteRange buffer, std::size_t width, Point point, Color color, uint8_t opa) {};
        virtual void Clear(infra::ConstByteRange buffer) {};
        virtual void CleanDCache() {};
    };

    class DriverGpu
    {
#if 0
/*
        - void * buf Pointer to a buffer to draw into
        - lv_area_t * buf_area The position and size of buf (absolute coordinates)
        - const lv_area_t * clip_area The current clip area with absolute coordinates, always the same or smaller than buf_area. All drawings should be clipped to this area.
        - void (*draw_rect)() Draw a rectangle with shadow, gradient, border, etc.
        - void (*draw_arc)() Draw an arc
        - void (*draw_img_decoded)() Draw an (A)RGB image that is already decoded by LVGL.
        - lv_res_t (*draw_img)() Draw an image before decoding it (it bypasses LVGL's internal image decoders)
        - void (*draw_letter)() Draw a letter
        - void (*draw_line)() Draw a line
        - void (*draw_polygon)() Draw a polygon
        - void (*draw_bg)() Replace the buffer with a rect without decoration like radius or borders.
        - void (*wait_for_finish)() Wait until all background operation are finished. (E.g. GPU operations)
        - void * user_data Custom user data for arbitrary purpose
*/
#endif
    };

    using Input = lv_indev_data_t;
    using Keypad = uint32_t;
    using ButtonId = uint32_t;
    using Encoder = int16_t;

    class DriverInputDevice
    {
    public:
        enum class InputType : uint8_t
        {
            none = LV_INDEV_TYPE_NONE,
            pointer = LV_INDEV_TYPE_POINTER,
            keypad = LV_INDEV_TYPE_KEYPAD,
            button = LV_INDEV_TYPE_BUTTON,
            encoder = LV_INDEV_TYPE_ENCODER,
        };

        enum class State : uint8_t
        {
            released,
            pressed,
        };

        struct Response
        {
            infra::Variant<Point, Keypad, ButtonId, Encoder> action;
            State state;
            bool continueReading;
        };

        explicit DriverInputDevice(InputType inputType)
            : inputType(inputType)
        {}
        virtual ~DriverInputDevice() = default;

        InputType Type() const
        {
            return inputType;
        }

        virtual Response Read() = 0;
        virtual void Feedback() = 0;

    private:
        InputType inputType;
    };

    class Controller
    {
    public:
        explicit Controller(DriverDisplay& display, DriverInputDevice& inputDevice);
        ~Controller();

        // Add input device...

    private:
        void DisplayInitialization();
        void InputDeviceInitialization();

    private:
        static void StaticLvglFlush(struct _lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);
        static void StaticLvglSetPixel(struct _lv_disp_drv_t * disp_drv, uint8_t * buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa);
        static void StaticLvglClear(struct _lv_disp_drv_t * disp_drv, uint8_t * buf, uint32_t size);
        static void StaticLvglCleanDCache(struct _lv_disp_drv_t * disp_drv);
        static void StaticLvglDrawInit(struct _lv_disp_drv_t * disp_drv, lv_draw_ctx_t * draw_ctx);
        static void StaticLvglDrawDeInit(struct _lv_disp_drv_t * disp_drv, lv_draw_ctx_t * draw_ctx);

        static void StaticLvglRead(struct _lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
        static void StaticLvglFeedback(struct _lv_indev_drv_t *, uint8_t);


    private:
        DriverDisplay& display;
        DriverInputDevice& inputDevice;
        lv_disp_t* lvglDisplay = nullptr;
        lv_indev_t* lvglInput = nullptr;
        lv_disp_drv_t lvglDisplayDescriptor;
        lv_indev_drv_t lvglInputDescriptor;
        lv_disp_draw_buf_t lvglDrawBuffers;
        infra::TimerRepeating tick;
    };
}

#endif

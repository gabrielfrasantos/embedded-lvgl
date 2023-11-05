#ifndef EMBEDDED_LVGL_WIDGET_LED_HPP
#define EMBEDDED_LVGL_WIDGET_LED_HPP

#include "lvgl.h"
#include "hal/interfaces/DisplayLcd.hpp"
#include "lvgl/core/Object.hpp"
#include "lvgl/core/Position.hpp"
#include "lvgl/core/Scroll.hpp"
#include <cstdint>


namespace embedded::lvgl::widget
{
    class Led
        : public core::Object
        , public core::Position
        , public core::Scroll
    {
    public:
        explicit Led(core::Object& parent, const hal::Color& color);
        virtual ~Led();

        void On();
        void Off();
        void Toggle();

    private:
        Object& parent;
        lv_obj_t * led;
    };
}

#endif

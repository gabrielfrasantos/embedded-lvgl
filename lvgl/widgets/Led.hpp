#ifndef EMBEDDED_LVGL_WIDGET_LED_HPP
#define EMBEDDED_LVGL_WIDGET_LED_HPP

#include "lvgl.h"
#include "lvgl/core/Color.hpp"
#include "lvgl/core/Object.hpp"
#include "lvgl/core/Position.hpp"
#include "lvgl/core/Scroll.hpp"
#include <cstdint>

namespace embedded::lvgl::widget
{
    using namespace embedded::lvgl::core;

    class Led
        : public Position
        , public Scroll
    {
    public:
        explicit Led(Object& parent, const Color& color);
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

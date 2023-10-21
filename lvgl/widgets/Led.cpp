#include "lvgl/widgets/Led.hpp"
#include <src/extra/widgets/led/lv_led.h>

namespace embedded::lvgl::widget
{
    Led::Led(Object& parent, const Color& color)
        : parent(parent)
    {
        lv_color_t c;

        c.full = color.Full();

        led = lv_led_create(&parent.Parent());
        embedded::lvgl::core::Position::SetObject(*led);
        embedded::lvgl::core::Scroll::SetObject(*led);
        lv_led_set_color(led, c);
        lv_led_set_brightness(led, LV_LED_BRIGHT_MAX);
    }

    Led::~Led()
    {
        lv_obj_del(led);
    }

    void Led::On()
    {
        lv_led_on(led);
    }

    void Led::Off()
    {
        lv_led_off(led);
    }

    void Led::Toggle()
    {
        lv_led_toggle(led);
    }
}
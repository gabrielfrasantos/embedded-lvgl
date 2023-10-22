#include "lvgl/core/Color.hpp"

namespace embedded::lvgl::core
{
    Color::Color(uint8_t red, uint8_t green, uint8_t blue)
        : color(red << 16 | green << 8 | blue)
    {}

    Color::Color(uint32_t color)
        : color(color)
    {}

    Color::Color(Rgb color)
        : color(static_cast<uint32_t>(color))
    {}

    Color::Color()
        : color(0)
    {}

    uint8_t Color::Red() const
    {
        return (color >> 16) & 0xff;
    }

    uint8_t Color::Green() const
    {
        return (color >> 8) & 0xff;
    }

    uint8_t Color::Blue() const
    {
        return color & 0xff;
    }
}
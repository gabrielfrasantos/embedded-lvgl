#ifndef EMBEDDED_LVGL_CORE_COLOR_HPP
#define EMBEDDED_LVGL_CORE_COLOR_HPP

#include <cstddef>
#include <cstdint>

namespace embedded::lvgl::core
{
    class Color
    {
    public:
        explicit Color();
        Color(uint8_t red, uint8_t green, uint8_t blue);
        Color(uint32_t color);

        uint8_t Red() const;
        uint8_t Green() const;
        uint8_t Blue() const;

        uint32_t Full() const
        {
            return color;
        }

    private:
        uint32_t color;
    };
}

#endif

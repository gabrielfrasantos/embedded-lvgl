#ifndef EMBEDDED_LVGL_CORE_POSITION_HPP
#define EMBEDDED_LVGL_CORE_POSITION_HPP

#include "lvgl.h"
#include <cstddef>

namespace embedded::lvgl::core
{
    class Position
    {
    public:
        virtual ~Position() = default;

        enum class Alignment : uint8_t
        {
            none = LV_ALIGN_DEFAULT,
            topLeft = LV_ALIGN_TOP_LEFT,
            topMiddle = LV_ALIGN_TOP_MID,
            topRight = LV_ALIGN_TOP_RIGHT,
            bottomLeft = LV_ALIGN_BOTTOM_LEFT,
            bottomMiddle = LV_ALIGN_BOTTOM_MID,
            bottomRight = LV_ALIGN_BOTTOM_RIGHT,
            leftMiddle = LV_ALIGN_LEFT_MID,
            rightMiddle = LV_ALIGN_RIGHT_MID,
            center = LV_ALIGN_CENTER,
            outTopLeft = LV_ALIGN_OUT_TOP_LEFT,
            outTopMiddle = LV_ALIGN_OUT_TOP_MID,
            outTopRight = LV_ALIGN_OUT_TOP_RIGHT,
            outBottomLeft = LV_ALIGN_OUT_BOTTOM_LEFT,
            outBottomMiddle = LV_ALIGN_OUT_BOTTOM_MID,
            outBottomRight = LV_ALIGN_OUT_BOTTOM_RIGHT,
            outLeftTop = LV_ALIGN_OUT_LEFT_TOP,
            outLeftMiddle = LV_ALIGN_OUT_LEFT_MID,
            outLeftRight = LV_ALIGN_OUT_LEFT_BOTTOM,
            outRightTop = LV_ALIGN_OUT_RIGHT_TOP,
            outRightMiddle = LV_ALIGN_OUT_RIGHT_MID,
            outRightBottom = LV_ALIGN_OUT_RIGHT_BOTTOM,
        };

        void Location(std::size_t x, std::size_t y);
        void LocationX(std::size_t x);
        void LocationY(std::size_t y);

        void Size(std::size_t width, std::size_t length);
        void Width(std::size_t width);
        void Height(std::size_t height);

        void ContentWidth(std::size_t width);
        void ContentHeight(std::size_t height);

        void Align(Alignment align);
        void Align(Alignment align, std::size_t xOffset, std::size_t yOffset);
        void AlignTo(Position& parent, Alignment align, std::size_t xOffset, std::size_t yOffset);

    protected:
        void SetObject(_lv_obj_t& object);

    private:
        _lv_obj_t* object = nullptr;
    };
}

#endif

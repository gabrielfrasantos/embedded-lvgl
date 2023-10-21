#include "lvgl/core/Position.hpp"
#include <src/core/lv_obj.h>
#include <src/hal/lv_hal_indev.h>
#include <src/misc/lv_area.h>

namespace embedded::lvgl::core
{
    void Position::SetObject(_lv_obj_t& object)
    {
        this->object = &object;
    }

    void Position::Location(std::size_t x, std::size_t y)
    {
        lv_obj_set_pos(object, x, y);
    }

    void Position::LocationX(std::size_t x)
    {
        lv_obj_set_x(object, x);
    }

    void Position::LocationY(std::size_t y)
    {
        lv_obj_set_y(object, y);
    }

    void Position::Size(std::size_t width, std::size_t height)
    {
        lv_obj_set_size(object, width, height);
    }

    void Position::Width(std::size_t width)
    {
        lv_obj_set_width(object, width);
    }

    void Position::Height(std::size_t height)
    {
        lv_obj_set_height(object, height);
    }

    void Position::ContentWidth(std::size_t width)
    {
        lv_obj_set_content_width(object, width);
    }

    void Position::ContentHeight(std::size_t height)
    {
        lv_obj_set_content_height(object, height);
    }

    void Position::Align(Alignment align)
    {
        lv_obj_set_align(object, static_cast<uint8_t>(align));
    }

    void Position::Align(Alignment align, std::size_t xOffset, std::size_t yOffset)
    {
        lv_obj_align(object, static_cast<uint8_t>(align), xOffset, yOffset);
    }

    void Position::AlignTo(Position& parent, Alignment align, std::size_t xOffset, std::size_t yOffset)
    {
        lv_obj_align_to(object, parent.object, static_cast<uint8_t>(align), xOffset, yOffset);
    }
}
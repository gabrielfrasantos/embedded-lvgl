#include "lvgl/core/Scroll.hpp"
#include <src/core/lv_obj.h>
#include <src/hal/lv_hal_indev.h>
#include <src/misc/lv_area.h>

namespace embedded::lvgl::core
{
    void Scroll::SetObject(_lv_obj_t& object)
    {
        this->object = &object;
    }

    void Scroll::Mode(enum Mode mode)
    {
        lv_obj_set_scrollbar_mode(object, static_cast<uint8_t>(mode));
    }

    void Scroll::Direction(enum Direction direction)
    {
        lv_obj_set_scroll_dir(object, static_cast<uint8_t>(direction));
    }

    void Scroll::SnapHorizontal(Snap snap)
    {
        lv_obj_set_scroll_snap_x(object, static_cast<uint8_t>(snap));
    }

    void Scroll::SnapVertical(Snap snap)
    {
        lv_obj_set_scroll_snap_y(object, static_cast<uint8_t>(snap));
    }
}
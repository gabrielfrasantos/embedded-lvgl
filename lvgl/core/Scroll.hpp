#ifndef EMBEDDED_LVGL_CORE_SCROLL_HPP
#define EMBEDDED_LVGL_CORE_SCROLL_HPP

#include "lvgl.h"
#include <cstddef>

namespace embedded::lvgl::core
{
    class Scroll
    {
    public:
        virtual ~Scroll() = default;

        enum class Mode : uint8_t
        {
            off = LV_SCROLLBAR_MODE_OFF,
            on = LV_SCROLLBAR_MODE_ON,
            active = LV_SCROLLBAR_MODE_ACTIVE,
            automatic = LV_SCROLLBAR_MODE_AUTO,
        };

        enum class Snap : uint8_t
        {
            none = LV_SCROLL_SNAP_NONE,
            start = LV_SCROLL_SNAP_START,
            end = LV_SCROLL_SNAP_END,
            center = LV_SCROLL_SNAP_CENTER,
        };

        enum class Direction : uint8_t
        {
            none = LV_DIR_NONE,
            left = LV_DIR_LEFT,
            right = LV_DIR_RIGHT,
            top = LV_DIR_TOP,
            bottom = LV_DIR_BOTTOM,
            horizontal = LV_DIR_HOR,
            vertical = LV_DIR_VER,
            all = LV_DIR_ALL,
        };

        void Mode(Mode mode);
        void Direction(Direction direction);
        void SnapHorizontal(Snap snap);
        void SnapVertical(Snap snap);

    protected:
        void SetObject(_lv_obj_t& object);

    private:
        _lv_obj_t* object = nullptr;
    };
}

#endif

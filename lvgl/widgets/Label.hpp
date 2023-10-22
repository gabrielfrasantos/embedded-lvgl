#ifndef EMBEDDED_LVGL_WIDGET_LABEL_HPP
#define EMBEDDED_LVGL_WIDGET_LABEL_HPP

#include "lvgl.h"
#include "lvgl/core/Color.hpp"
#include "lvgl/core/Object.hpp"
#include "lvgl/core/Position.hpp"
#include "lvgl/core/Scroll.hpp"
#include "infra/util/BoundedString.hpp"
#include <cstdint>

namespace embedded::lvgl::widget
{
    using namespace embedded::lvgl::core;

    class Label
        : public Object
        , public Position
        , public Scroll
    {
    public:
        enum class Mode
        {
            wrap = LV_LABEL_LONG_WRAP, /**< Keep the object width, wrap the too long lines and expand the object height*/
            dot = LV_LABEL_LONG_DOT, /**< Keep the size and write dots at the end if the text is too long*/
            scroll = LV_LABEL_LONG_SCROLL, /**< Keep the size and roll the text back and forth*/
            scrollCircularLV_LABEL_LONG_SCROLL_CIRCULAR, /**< Keep the size and roll the text circularly*/
            clip = LV_LABEL_LONG_CLIP, /**< Keep the size and clip the text out of it*/
        };

        explicit Label(Object& parent, infra::BoundedConstString text, Mode mode = Mode::wrap);
        ~Label() override;

    private:
        Object& parent;
        lv_obj_t * label;
    };
}

#endif

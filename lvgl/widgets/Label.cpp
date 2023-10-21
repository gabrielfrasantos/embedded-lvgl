#include "lvgl/widgets/Label.hpp"
#include <src/extra/widgets/led/lv_led.h>
#include "infra/util/ReallyAssert.hpp"

namespace embedded::lvgl::widget
{
    Label::Label(Object& parent, infra::BoundedString& text, Mode mode)
        : parent(parent)
    {
        really_assert(!text.full());
        text.append("\0");
        label = lv_label_create(&parent.Parent());
        embedded::lvgl::core::Position::SetObject(*label);
        embedded::lvgl::core::Scroll::SetObject(*label);
        lv_label_set_text_static(label, text.cbegin());
        lv_label_set_long_mode(label, static_cast<uint8_t>(mode));
        lv_label_set_recolor(label, true);
    }

    Label::~Label()
    {
        lv_obj_del(label);
    }
}
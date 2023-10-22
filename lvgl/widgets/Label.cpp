#include "lvgl/widgets/Label.hpp"

namespace embedded::lvgl::widget
{
    Label::Label(Object& parent, infra::BoundedConstString text, Mode mode)
        : parent(parent)
    {
        label = lv_label_create(&parent.Parent());
        embedded::lvgl::core::Object::SetObject(*label);
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
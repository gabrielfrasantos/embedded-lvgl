#include "lvgl/widgets/Button.hpp"
#include <src/core/lv_event.h>

namespace embedded::lvgl::widget
{
    Button::Button(Object& parent)
        : parent(parent)
    {
        button = lv_btn_create(&parent.Parent());
        embedded::lvgl::core::Object::SetObject(*button);
        embedded::lvgl::core::Position::SetObject(*button);
        embedded::lvgl::core::Scroll::SetObject(*button);
        lv_obj_add_event_cb(button, Event, LV_EVENT_ALL, this);
    }

    Button::~Button()
    {
        lv_obj_remove_event_cb(button, Event);
        lv_obj_del(button);
    }

    void Button::TriggerPressedEvent()
    {
        lv_event_send(button, LV_EVENT_PRESSED, nullptr);
    }

    void Button::TriggerPressingEvent()
    {
        lv_event_send(button, LV_EVENT_PRESSING, nullptr);
    }

    void Button::TriggerLongPressedEvent()
    {
        lv_event_send(button, LV_EVENT_LONG_PRESSED, nullptr);
    }

    void Button::TriggerReleasedEvent()
    {
        lv_event_send(button, LV_EVENT_RELEASED, nullptr);
    }

    void Button::OnPressed(const infra::Function<void()>& onPressed)
    {
        this->onPressed = onPressed;
    }

    void Button::OnPressing(const infra::Function<void()>& onPressing)
    {
        this->onPressing = onPressing;
    }

    void Button::OnLongPressed(const infra::Function<void()>& onLongPressed)
    {
        this->onLongPressed = onLongPressed;
    }

    void Button::OnReleased(const infra::Function<void()>& onReleased)
    {
        this->onReleased = onReleased;
    }

    void Button::Event(lv_event_t * event)
    {
        auto code = lv_event_get_code(event);
        auto object = reinterpret_cast<Button *>(lv_event_get_user_data(event));

        if (code == LV_EVENT_PRESSED && object->onPressed)
            object->onPressed();

        if (code == LV_EVENT_PRESSING && object->onPressing)
            object->onPressing();

        if (code == LV_EVENT_LONG_PRESSED && object->onLongPressed)
            object->onLongPressed();

        if (code == LV_EVENT_RELEASED && object->onReleased)
            object->onReleased();
    }
}
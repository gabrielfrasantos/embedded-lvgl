#ifndef EMBEDDED_LVGL_WIDGET_BUTTON_HPP
#define EMBEDDED_LVGL_WIDGET_BUTTON_HPP

#include "infra/util/Function.hpp"
#include "lvgl.h"
#include "lvgl/core/Object.hpp"
#include "lvgl/core/Position.hpp"
#include "lvgl/core/Scroll.hpp"
#include "infra/util/IntrusiveList.hpp"
#include <cstdint>

namespace embedded::lvgl::widget
{
    using namespace embedded::lvgl::core;

    class Button
        : public Object
        , public Position
        , public Scroll
        , public infra::IntrusiveList<Button>::NodeType
    {
    public:
        explicit Button(Object& parent);
        virtual ~Button();

        void TriggerPressedEvent();
        void TriggerPressingEvent();
        void TriggerLongPressedEvent();
        void TriggerReleasedEvent();

        void OnPressed(const infra::Function<void()>& onPressed);
        void OnPressing(const infra::Function<void()>& onPressing);
        void OnLongPressed(const infra::Function<void()>& onLongPressed);
        void OnReleased(const infra::Function<void()>& onReleased);

    private:
        static void Event(lv_event_t * e);

    private:
        Object& parent;
        lv_obj_t * button;
        infra::Function<void()> onPressed;
        infra::Function<void()> onPressing;
        infra::Function<void()> onLongPressed;
        infra::Function<void()> onReleased;
    };
}

#endif

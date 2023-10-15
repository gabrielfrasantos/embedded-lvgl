#ifndef EMBEDDED_LVGL_WIDGET_LED_HPP
#define EMBEDDED_LVGL_WIDGET_LED_HPP

#include "infra/util/ByteRange.hpp"
#include "infra/util/Function.hpp"
#include "infra/util/BoundedVector.hpp"
#include "infra/timer/Timer.hpp"
#include "infra/util/Variant.hpp"
#include "lvgl.h"
#include <sys/_stdint.h>

namespace embedded::lvgl::widget
{
    class Led
        // : public object
    {
    public:
        explicit Led(/* Color and brightness */);
        virtual ~Led() = default;

        void On();
        void Off();
        void Toggle();
    };
}

#endif

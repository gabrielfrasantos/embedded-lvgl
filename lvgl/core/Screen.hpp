#ifndef EMBEDDED_LVGL_CORE_SCREEN_HPP
#define EMBEDDED_LVGL_CORE_SCREEN_HPP

#include "lvgl/core/Object.hpp"

namespace embedded::lvgl::core
{
    class Screen
    {
    public:
        virtual ~Screen() = default;

        void Load(Object::ParentObject&) const;
        Object::ParentObject& Active();
        Object::ParentObject& TopLayer();
    };
}

#endif

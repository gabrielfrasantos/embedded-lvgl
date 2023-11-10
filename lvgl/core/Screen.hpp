#ifndef EMBEDDED_LVGL_CORE_SCREEN_HPP
#define EMBEDDED_LVGL_CORE_SCREEN_HPP

#include "lvgl/core/Object.hpp"
#include "infra/util/InterfaceConnector.hpp"

namespace embedded::lvgl::core
{
    class Screen
        : public infra::InterfaceConnector<Screen>
        , public Object
    {
    public:
        Screen();
        virtual ~Screen() = default;

        void Load(Object::ParentObject&) const;
        Object::ParentObject& Active();
        Object::ParentObject& TopLayer();
    };
}

#endif

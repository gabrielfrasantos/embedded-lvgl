#ifndef EMBEDDED_LVGL_CORE_OBJECT_HPP
#define EMBEDDED_LVGL_CORE_OBJECT_HPP

#include "lvgl.h"
#include <cstddef>

namespace embedded::lvgl::core
{
    class Object
    {
    public:
        using ParentObject = lv_obj_t;

        virtual ~Object() = default;
        ParentObject& Parent();

    protected:
        void SetObject(_lv_obj_t& object);

    private:
        _lv_obj_t* object = nullptr;
    };
}

#endif

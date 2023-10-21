#include "lvgl/core/Object.hpp"

namespace embedded::lvgl::core
{
    void Object::SetObject(_lv_obj_t& object)
    {
        this->object = &object;
    }

    Object::ParentObject& Object::Parent()
    {
        return *this->object;
    }
}
#include "lvgl/core/Screen.hpp"

namespace embedded::lvgl::core
{
    Screen::Screen()
    {
        this->SetObject(*lv_scr_act());
    }

    void Screen::Load(Object::ParentObject& screen) const
    {
        lv_scr_load(&screen);
    }

    Object::ParentObject& Screen::Active()
    {
        return *lv_scr_act();
    }

    Object::ParentObject& Screen::TopLayer()
    {
        return *lv_layer_top();
    }
}
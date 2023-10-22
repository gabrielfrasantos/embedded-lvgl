#include "infra/util/BoundedString.hpp"
#include "lvgl/core/Screen.hpp"
#include "lvgl/core/Scroll.hpp"
#include "lvgl/widgets/Button.hpp"
#include "lvgl/widgets/Led.hpp"
#include "lvgl/widgets/Label.hpp"

int main()
{
    using namespace embedded::lvgl::core;
    using namespace embedded::lvgl::widget;

    static Screen screen;
    static Color red(Color::Rgb::red);
    static Color blue(Color::Rgb::blue);
    static Color green(Color::Rgb::green);

    static Led led1(screen, red);
    static Led led2(screen, blue);
    static Led led3(screen, green);

    static Label labelLed1(screen, infra::BoundedConstString("Led1\0"));
    static Label labelLed2(screen, infra::BoundedConstString("Led2\0"));
    static Label labelLed3(screen, infra::BoundedConstString("Led3\0"));

    static Button button1(screen);
    static Button button2(screen);
    static Button button3(screen);

    static Label labelButton1(button1, infra::BoundedConstString("Button1\0"));
    static Label labelButton2(button2, infra::BoundedConstString("Button2\0"));
    static Label labelButton3(button3, infra::BoundedConstString("Button3\0"));

    led1.Align(Position::Alignment::topMiddle, -120, 0);
    led2.Align(Position::Alignment::topMiddle, 0, 0);
    led3.Align(Position::Alignment::topMiddle, 120, 0);

    labelLed1.AlignTo(led1, Position::Alignment::center, 0, 25);
    labelLed2.AlignTo(led2, Position::Alignment::center, 0, 25);
    labelLed3.AlignTo(led3, Position::Alignment::center, 0, 25);

    labelButton1.Align(Position::Alignment::center, 0, 0);
    labelButton2.Align(Position::Alignment::center, 0, 0);
    labelButton3.Align(Position::Alignment::center, 0, 0);

    button1.OnReleased([]()
        {
            led1.Toggle();
        });

    button2.OnReleased([]()
        {
            led2.Toggle();
        });

    button3.OnReleased([]()
        {
            led3.Toggle();
        });

    __builtin_unreachable();
}

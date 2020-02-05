#include "common/runtime.h"
#include "common/input.h"

std::vector<std::string> buttons = {
    "a", "b", "back", "start",
    "dpright", "dpleft", "dpup", "dpdown",
    "rightshoulder", "leftshoulder", "x", "y",
    "", "", "zl", "zr",
    "", "", "", "",
    "touch", "", "", "",
    "", "", "", "",
    "", "", "", ""
};

bool Input::PollEvent(LOVE_Event * event)
{
    hidScanInput();

    u32 keyDown = hidKeysDown();
    for (int index = 0; index < 32; index++)
    {
        if (keyDown & BIT(index) && Input::IsValid(buttons[index]))
        {
            event->type = LOVE_GAMEPADDOWN;

            event->button.id = index;
            event->button.name = buttons[index];

            return true;
        }
    }


    u32 keyUp = hidKeysUp();
    for (int index = 0; index < 32; index++)
    {
        if (keyUp & BIT(index) && Input::IsValid(buttons[index]))
        {
            event->type = LOVE_GAMEPADUP;

            event->button.id = keyDown;
            event->button.name = buttons[index];

            return true;
        }
    }

    // circlePosition position;
    // hidCircleRead(&position);

    // // clearly not a good way to do this..
    // if (position.dx != m_lastPosition[0].dx)
    // {
    //     event->type = LOVE_GAMEPADAXIS;
    //     event->axis.axis = "leftx";
    //     event->axis.value = position.dx;

    //     m_lastPosition[0].dx = position.dx;

    //     return true;
    // }

    // if (position.dy != m_lastPosition[0].dy)
    // {
    //     event->type = LOVE_GAMEPADAXIS;
    //     event->axis.axis = "lefty";
    //     event->axis.value = position.dy;

    //     m_lastPosition[0].dy = position.dy;

    //     return true;
    // }

    return false;
}

#include "common/runtime.h"
#include "common/input.h"

std::array<std::string, 32> buttons = {
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

    // Check for 'press'
    u32 keyDown = hidKeysDown();
    for (unsigned int index = 0; index < buttons.size(); index++)
    {
        if (keyDown & BIT(index) && buttons[index] != "touch")
        {
            event->type = LOVE_GAMEPADDOWN;

            event->button.id = keyDown;
            event->button.name = buttons[index].c_str();

            return true;
        }
    }

    u32 keyUp = hidKeysUp();
    for (unsigned int index = 0; index < buttons.size(); index++)
    {
        if (keyUp & BIT(index) && buttons[index] != "touch")
        {
            event->type = LOVE_GAMEPADUP;

            event->button.id = keyDown;
            event->button.name = buttons[index].c_str();

            return true;
        }
    }

    circlePosition position;
    hidCircleRead(&position);

    // clearly not a good way to do this..
    if (position.dx != m_lastPosition[0].dx)
    {
        event->type = LOVE_GAMEPADAXIS;
        event->axis.axis = "leftx";
        event->axis.value = position.dx;

        m_lastPosition[0].dx = position.dx;

        return true;
    }

    if (position.dy != m_lastPosition[0].dy)
    {
        event->type = LOVE_GAMEPADAXIS;
        event->axis.axis = "lefty";
        event->axis.value = position.dy;

        m_lastPosition[0].dy = position.dy;

        return true;
    }

    return false;
}

#include "common/runtime.h"
#include "common/backend/input.h"

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

    touchPosition touch;
    hidTouchRead(&touch);

    for (unsigned int index = 0; index < buttons.size(); index++)
    {
        if (keyDown & BIT(index))
        {
            if (Input::IsValid(buttons[index]))
            {
                event->type = LOVE_GAMEPADDOWN;

                event->button.id = index;
                event->button.name = buttons[index];

                return true;
            }
            else if (buttons[index] == "touch")
            {
                event->type = LOVE_TOUCHPRESS;

                event->touch.id = 1;
                event->touch.x = touch.px;
                event->touch.y = touch.py;

                m_lastTouch = { touch.px, touch.py };

                return true;
            }
        }
    }


    u32 keyUp = hidKeysUp();
    for (unsigned int index = 0; index < buttons.size(); index++)
    {
        if (keyUp & BIT(index))
        {
            if (Input::IsValid(buttons[index]))
            {
                event->type = LOVE_GAMEPADUP;

                event->button.id = index;
                event->button.name = buttons[index];

                return true;
            }
            else
            {
                event->type = LOVE_TOUCHRELEASE;

                event->touch.id = 1;
                event->touch.x = m_lastTouch[0];
                event->touch.y = m_lastTouch[1];

                return true;
            }
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

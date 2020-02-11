#include "common/runtime.h"
#include "common/backend/input.h"

std::vector<std::string> Input::GetButtons()
{
    return
    {
        "a", "b", "back", "start",
        "dpright", "dpleft", "dpup", "dpdown",
        "rightshoulder", "leftshoulder", "x", "y",
        "", "", "KEY_ZL", "KEY_ZR",
        "", "", "", "",
        "touch", "", "", "",
        "KEY_CSTICK_RIGHT", "KEY_CSTICK_LEFT", "KEY_CSTICK_UP", "KEY_CSTICK_DOWN",
        "KEY_CPAD_RIGHT", "KEY_CPAD_LEFT", "KEY_CPAD_UP", "KEY_CPAD_DOWN"
    };
}

bool Input::PollEvent(LOVE_Event * event)
{
    hidScanInput();

    m_keyDown = hidKeysDown();

    touchPosition touch;
    hidTouchRead(&touch);

    auto buttons = Input::GetButtons();

    for (unsigned int index = 0; index < buttons.size(); index++)
    {
        if (m_keyDown & BIT(index))
        {
            if (Input::IsValid(buttons[index]))
            {
                event->type = LOVE_GAMEPADDOWN;

                event->button.which = 0;
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


    m_keyUp = hidKeysUp();
    for (unsigned int index = 0; index < buttons.size(); index++)
    {
        if (m_keyUp & BIT(index))
        {
            if (Input::IsValid(buttons[index]))
            {
                event->type = LOVE_GAMEPADUP;

                event->button.which = 0;
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

    m_keyHeld = hidKeysHeld();

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

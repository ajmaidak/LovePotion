#include "common/runtime.h"
#include "common/backend/input.h"

std::map<std::string, int> Input::GetButtons()
{
    return
    {
        { "a", KEY_A}, { "b", KEY_B }, { "x", KEY_X }, { "y", KEY_Y },
        { "dpright", KEY_DRIGHT}, { "dpleft", KEY_DLEFT },
        { "dpup", KEY_DUP }, { "dpdown", KEY_DDOWN }, { "rightshoulder", KEY_R },
        { "leftshoulder", KEY_L }, { "back", KEY_SELECT }, { "start", KEY_START}
    };
}

bool Input::PollEvent(LOVE_Event * event)
{
    hidScanInput();

    touchPosition touch;
    hidTouchRead(&touch);

    auto buttons = Input::GetButtons();

    m_keyDown = hidKeysDown();
    for (auto it = buttons.begin(); it != buttons.end(); it++)
    {
        if (Input::GetKeyDown<u32>() & it->second)
        {
            event->type = LOVE_GAMEPADDOWN;

            event->button.name = it->first;
            event->button.which = 0;

            return true;
        }
    }

    if (Input::GetKeyUp<u32>() & KEY_TOUCH)
    {
        event->type = LOVE_TOUCHPRESS;

        event->touch.id = 1;

        event->touch.x = touch.px;
        event->touch.y = touch.py;

        m_lastTouch[0] = touch.px;
        m_lastTouch[1] = touch.py;

        return true;
    }


    m_keyUp = hidKeysUp();
    for (auto it = buttons.begin(); it != buttons.end(); it++)
    {
        if (Input::GetKeyUp<u32>() & it->second)
        {
            event->type = LOVE_GAMEPADUP;

            event->button.name = it->first;
            event->button.which = 0;

            return true;
        }
    }

    if (Input::GetKeyUp<u32>() & KEY_TOUCH)
    {
        event->type = LOVE_TOUCHRELEASE;

        event->touch.id = 1;
        event->touch.x = m_lastTouch[0];
        event->touch.y = m_lastTouch[1];

        return true;
    }

    m_keyHeld = hidKeysHeld();

    circlePosition position;
    hidCircleRead(&position);

    // clearly not a good way to do this..
    if (position.dx != m_lastPosition[0].dx)
    {
        event->type = LOVE_GAMEPADAXIS;

        event->axis.axis = "leftx";
        event->axis.which = 0;

        m_lastPosition[0].dx = position.dx;

        return true;
    }

    if (position.dy != m_lastPosition[0].dy)
    {
        event->type = LOVE_GAMEPADAXIS;

        event->axis.axis = "lefty";
        event->axis.which = 0;

        m_lastPosition[0].dy = position.dy;

        return true;
    }

    return false;
}

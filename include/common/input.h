/*
** input.h
** Handles internal input handling
*/

#pragma once

struct GamePadButton
{
    const char * name;
    int id;
};

struct GamePadAxis
{
    const char * axis;
    float value;
};

struct LOVE_Event
{
    int type;
    int which;

    GamePadButton button;
    GamePadAxis axis;
};

enum LOVE_EventType
{
    LOVE_GAMEPADAXIS,
    LOVE_GAMEPADDOWN,
    LOVE_GAMEPADUP,
    LOVE_TOUCHPRESS,
    LOVE_TOUCHRELEASE,
    LOVE_TOUCHMOVED
};

class Input
{
    public:
        static bool PollEvent(LOVE_Event * event);

    private:
        static inline StickPosition m_lastPosition[2] = {};
};

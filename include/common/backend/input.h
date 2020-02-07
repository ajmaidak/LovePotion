/*
** input.h
** Handles internal input handling
*/

#pragma once

struct GamePadButton
{
    std::string name;
    int id;
};

struct GamePadAxis
{
    const char * axis;
    float value;
};

struct Touch
{
    int id;
    int x;
    int y;
};

struct LOVE_Event
{
    int type;
    int which;

    GamePadButton button;
    GamePadAxis axis;
    Touch touch;
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
        static std::vector<std::string> GetButtons();

    private:
        static inline StickPosition m_lastPosition[2] = {};
        static inline std::array<int, 2> m_lastTouch = { 0 };

        static inline bool IsValid(const std::string & name) {
            return !name.empty() && name != "touch";
        }
};

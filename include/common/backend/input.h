/*
** input.h
** Handles internal input handling
*/

#pragma once

struct GamePadButton
{
    std::string name;
    size_t which;
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

        static inline bool IsValid(const std::string & name) {
            return !name.empty() && name != "touch";
        }

        static inline u32 Input::GetKeyDown() {
            return m_keyDown;
        }

        static inline u32 Input::GetKeyUp() {
            return m_keyUp;
        }

        static inline u32 Input::GetKeyHeld() {
            return m_keyHeld;
        }

    private:
        static inline StickPosition m_lastPosition[2] = {};
        static inline std::array<int, 2> m_lastTouch = { 0 };

        static inline u32 m_keyDown = 0;
        static inline u32 m_keyUp = 0;
        static inline u32 m_keyHeld = 0;
};

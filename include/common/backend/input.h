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
    std::string axis;
    float value;
    int which;
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
        static inline std::map<std::string, int> GetButtons() { return m_buttons; }

        template <typename T>
        static inline T GetKeyDown() {
            return std::get<T>(m_keyDown);
        }

        template <typename T>
        static inline T GetKeyUp() {
            return std::get<T>(m_keyUp);
        }

        template <typename T>
        static inline T GetKeyHeld() {
            return std::get<T>(m_keyHeld);
        }

    private:
        static inline StickPosition m_lastPosition[2] = { { 0, 0 } };
        static inline std::array<int, 2> m_lastTouch = { 0, 0 };

        static std::map<std::string, int> m_buttons;

        static inline std::variant<u32, u64> m_keyDown = (u32)0;
        static inline std::variant<u32, u64> m_keyUp = (u32)0;
        static inline std::variant<u32, u64> m_keyHeld = (u32)0;
};

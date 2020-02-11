#pragma once

#include "objects/gamepad/gamepad.h"
#include "objects/gamepad/wrap_gamepad.h"

class Joystick
{
    public:
        static void Initialize();

        static Gamepad * GetJoystickFromID(size_t index);

        static void AddGamepad(Gamepad * gamepad);

        static int Register(lua_State * L);

    private:
        static inline std::vector<Gamepad *> m_gamepads = {};

        static int GetJoystickCount(lua_State * L);

        static int GetJoysticks(lua_State * L);
};

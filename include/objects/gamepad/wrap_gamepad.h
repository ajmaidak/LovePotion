#pragma once

#include "objects/gamepad/gamepad.h"
#include "modules/joystick.h"

namespace Wrap_Gamepad
{
    int New(lua_State * L);

    int GetID(lua_State * L);

    int IsGamepadDown(lua_State * L);

    int IsDown(lua_State * L);

    Gamepad * CheckJoystick(lua_State * L, int index);

    int Register(lua_State * L);
}

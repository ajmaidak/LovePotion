#pragma once

#include "objects/gamepad/gamepad.h"

namespace Wrap_Gamepad
{
    int New(lua_State * L);

    int __ToString(lua_State * L);

    int Register(lua_State * L);
}

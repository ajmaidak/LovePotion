#pragma once

#include "modules/event/event.h"

namespace Wrap_Event
{
    int Poll_I(lua_State * L);

    int Clear(lua_State * L);

    int Quit(lua_State * L);

    int Pump(lua_State * L);

    int Register(lua_State * L);
}

#include "common/runtime.h"
#include "window.h"

int Window::Register(lua_State * L)
{
    luaL_Reg reg[] =
    {
        { "setMode",            SetMode            },
        { "getFullscreenModes", GetFullscreenModes },
        { 0, 0 }
    };

    luaL_newlib(L, reg);

    return 1;
}

#include "common/runtime.h"
#include "modules/window.h"

// love.window.getFullscreenModes
int Window::GetFullscreenModes(lua_State * L)
{
    unsigned int display = luaL_optnumber(L, 1, 1);

    if (!display || display > 2)
        return luaL_error(L, "Invalid display index %d", display);

    lua_createtable(L, 1, 0);
    lua_pushnumber(L, 1);

    lua_createtable(L, 0, 2);

    //Inner table attributes
    lua_pushnumber(L, 1280);
    lua_setfield(L, -2, "width");

    lua_pushnumber(L, 720);
    lua_setfield(L, -2, "height");

    //End table attributes

    lua_settable(L, -3);

    return 1;
}

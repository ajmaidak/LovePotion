#include "common/runtime.h"
#include "modules/window.h"

#include "common/display.h"

// love.window.getFullscreenModes
int Window::GetFullscreenModes(lua_State * L)
{
    unsigned int display = luaL_optnumber(L, 1, 1);
    auto displaySizes = Display::GetWindowSizes();


    if (!display || display > displaySizes.size())
    {
        lua_newtable(L);
        return 1;
    }

    // We want to C index this. Max displays is 2
    // because the 3DS has two displays
    display = std::clamp((int)display - 1, 0, (int)displaySizes.size() - 1);

    lua_createtable(L, 1, 0);
    lua_pushnumber(L, 1);

    lua_createtable(L, 0, 2);

    //Inner table attributes
    lua_pushnumber(L, displaySizes[display].first);
    lua_setfield(L, -2, "width");

    lua_pushnumber(L, displaySizes[display].second);
    lua_setfield(L, -2, "height");
    //End table attributes

    lua_settable(L, -3);

    return 1;
}

int Window::GetDisplayCount(lua_State * L)
{
    lua_pushinteger(L, Display::GetDisplayCount());

    return 1;
}

int Window::IsOpen(lua_State * L)
{
    lua_pushboolean(L, Display::IsOpen());

    return 1;
}

int Window::Register(lua_State * L)
{
    luaL_Reg reg[] =
    {
        { "isOpen",             IsOpen             },
        { "setMode",            SetMode            },
        { "getDisplayCount",    GetDisplayCount    },
        { "getFullscreenModes", GetFullscreenModes },
        { 0,                    0                  }
    };

    WrappedModule module;
    module.name = "window";
    module.functions = reg;

    return Luax::RegisterModule(L, module);
}

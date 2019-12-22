#include "common/runtime.h"
#include "modules/graphics.h"

#include "common/display.h"

int Graphics::Clear(lua_State * L)
{
    Color clearColor = { 0, 0, 0, 1 };

    clearColor.r = luaL_checknumber(L, 1);
    clearColor.g = luaL_checknumber(L, 2);
    clearColor.b = luaL_checknumber(L, 3);

    Display::Clear(&clearColor);

    return 0;
}

int Graphics::GetBackgroundColor(lua_State * L)
{
    lua_pushnumber(L, m_background.r);
    lua_pushnumber(L, m_background.g);
    lua_pushnumber(L, m_background.b);

    return 3;
}

int Graphics::SetBackgroundColor(lua_State * L)
{
    if (lua_istable(L, 1))
    {
        for (int i = 1; i <= 3; i++)
            lua_rawgeti(L, 1, i);

        m_background.r = luaL_checknumber(L, -3);
        m_background.g = luaL_checknumber(L, -2);
        m_background.b = luaL_checknumber(L, -1);
    }
    else if (lua_isnumber(L, 1))
    {
        m_background.r = luaL_checknumber(L, 1);
        m_background.g = luaL_checknumber(L, 2);
        m_background.b = luaL_checknumber(L, 3);
    }

    return 0;
}

Color Graphics::GetBackgroundColor()
{
    return m_background;
}

int Graphics::Register(lua_State * L)
{
    luaL_Reg reg[] =
    {
        { "clear",              Clear              },
        { "setBackgroundColor", SetBackgroundColor },
        { "getBackgroundColor", GetBackgroundColor },
        { 0,                    0                  }
    };

    luaL_newlib(L, reg);

    return 1;
}

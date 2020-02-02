#include "common/runtime.h"
#include "modules/graphics.h"

#include "common/display.h"

int Graphics::Clear(lua_State * L)
{
    Color clearColor = { 0, 0, 0, 1 };

    float r = luaL_checknumber(L, 1);
    float g = luaL_checknumber(L, 2);
    float b = luaL_checknumber(L, 3);

    clearColor.r = std::clamp(r, 0.0f, 1.0f) * 255;
    clearColor.g = std::clamp(g, 0.0f, 1.0f) * 255;
    clearColor.b = std::clamp(b, 0.0f, 1.0f) * 255;

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
    float r = m_background.r;
    float g = m_background.g;
    float b = m_background.b;

    if (lua_istable(L, 1))
    {
        for (int i = 1; i <= 3; i++)
            lua_rawgeti(L, 1, i);

        r = luaL_checknumber(L, -3);
        g = luaL_checknumber(L, -2);
        b = luaL_checknumber(L, -1);
    }
    else if (lua_isnumber(L, 1))
    {
        r = luaL_checknumber(L, 1);
        g = luaL_checknumber(L, 2);
        b = luaL_checknumber(L, 3);
    }

    m_background.r = std::clamp(r, 0.0f, 1.0f) * 255;
    m_background.g = std::clamp(g, 0.0f, 1.0f) * 255;
    m_background.b = std::clamp(b, 0.0f, 1.0f) * 255;

    return 0;
}

int Graphics::GetColor(lua_State * L)
{
    lua_pushnumber(L, m_foreground.r);
    lua_pushnumber(L, m_foreground.g);
    lua_pushnumber(L, m_foreground.b);
    lua_pushnumber(L, m_foreground.a);

    return 4;
}

int Graphics::SetColor(lua_State * L)
{
    float r = m_foreground.r;
    float g = m_foreground.g;
    float b = m_foreground.b;
    float a = m_foreground.a;

    if (lua_istable(L, 1))
    {
        for (int i = 1; i <= 4; i++)
            lua_rawgeti(L, 1, i);

        r = luaL_checknumber(L, -4);
        g = luaL_checknumber(L, -3);
        b = luaL_checknumber(L, -2);
        a = luaL_optnumber(L, -1, 1);
    }
    else if (lua_isnumber(L, 1))
    {
        r = luaL_checknumber(L, 1);
        g = luaL_checknumber(L, 2);
        b = luaL_checknumber(L, 3);
        a = luaL_optnumber(L, 4, 1);
    }

    m_foreground.r = std::clamp(r, 0.0f, 1.0f) * 255;
    m_foreground.g = std::clamp(g, 0.0f, 1.0f) * 255;
    m_foreground.b = std::clamp(b, 0.0f, 1.0f) * 255;
    m_foreground.a = std::clamp(a, 0.0f, 1.0f) * 255;

    Display::SetBlendColor(&m_background);

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
        { "setColor",           SetColor           },
        { "getBackgroundColor", GetBackgroundColor },
        { "getColor",           GetColor           },
        { "present",            Display::Present   },
        { 0,                    0                  }
    };

    Module module;
    module.name = "graphics";
    module.functions = reg;

    return Luax::RegisterModule(L, module);
}

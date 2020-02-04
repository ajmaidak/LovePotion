#include "common/runtime.h"
#include "modules/graphics.h"

#include "common/display.h"

int Graphics::Clear(lua_State * L)
{
    Color clearColor = { 0, 0, 0, 1 };
    Color inputColor = clearColor;

    inputColor.r = luaL_checknumber(L, 1);
    inputColor.g = luaL_checknumber(L, 2);
    inputColor.b = luaL_checknumber(L, 3);

    AdjustColor(inputColor, &clearColor);

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
    Color currentBackground = m_background;

    if (lua_istable(L, 1))
    {
        for (int i = 1; i <= 3; i++)
            lua_rawgeti(L, 1, i);

        currentBackground.r = luaL_checknumber(L, -3);
        currentBackground.g = luaL_checknumber(L, -2);
        currentBackground.b = luaL_checknumber(L, -1);
    }
    else if (lua_isnumber(L, 1))
    {
        currentBackground.r = luaL_checknumber(L, 1);
        currentBackground.g = luaL_checknumber(L, 2);
        currentBackground.b = luaL_checknumber(L, 3);
    }

    AdjustColor(currentBackground, &m_background);

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
    Color currentBlend = m_foreground;

    if (lua_istable(L, 1))
    {
        for (int i = 1; i <= 4; i++)
            lua_rawgeti(L, 1, i);

        m_foreground.r = luaL_checknumber(L, -4);
        m_foreground.g = luaL_checknumber(L, -3);
        m_foreground.b = luaL_checknumber(L, -2);
        m_foreground.a = luaL_optnumber(L, -1, 1);
    }
    else if (lua_isnumber(L, 1))
    {
        m_foreground.r = luaL_checknumber(L, 1);
        m_foreground.g = luaL_checknumber(L, 2);
        m_foreground.b = luaL_checknumber(L, 3);
        m_foreground.a = luaL_optnumber(L, 4, 1);
    }

    AdjustColor(currentBlend, &m_foreground);

    Display::SetBlendColor(&m_background);

    return 0;
}

void Graphics::AdjustColor(const Color & in, Color * out)
{
    float mul = 255.0f;

    #if defined(_3DS)
        mul = 1.0f;
    #endif

    out->r = std::clamp(in.r, 0.0f, 1.0f) * mul;
    out->g = std::clamp(in.g, 0.0f, 1.0f) * mul;
    out->b = std::clamp(in.b, 0.0f, 1.0f) * mul;
    out->a = std::clamp(in.a, 0.0f, 1.0f) * mul;
}

int Graphics::Register(lua_State * L)
{
    luaL_Reg reg[] =
    {
        { "clear",              Clear              },
        { "getBackgroundColor", GetBackgroundColor },
        { "getColor",           GetColor           },
        { "present",            Display::Present   },
        { "setBackgroundColor", SetBackgroundColor },
        { "setColor",           SetColor           },
        { "setScreen",          Display::SetScreen },
        { 0,                    0                  }
    };

    Module module;
    module.name = "graphics";
    module.functions = reg;

    return Luax::RegisterModule(L, module);
}

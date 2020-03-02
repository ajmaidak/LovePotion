#include "common/runtime.h"
#include "objects/font/wrap_font.h"

love::Type love::Font::type("Font", &Object::type);

int Wrap_Font::GetWidth(lua_State * L)
{
    love::Font * self = Wrap_Font::CheckFont(L, 1);
    const char * text = luaL_checkstring(L, 2);

    lua_pushnumber(L, self->GetWidth(text));

    return 1;
}

int Wrap_Font::GetHeight(lua_State * L)
{
    love::Font * self = Wrap_Font::CheckFont(L, 1);

    float height = self->GetHeight();

    lua_pushnumber(L, height);

    return 1;
}

love::Font * Wrap_Font::CheckFont(lua_State * L, int index)
{
    return Luax::CheckType<love::Font>(L, index);
}

int Wrap_Font::Register(lua_State * L)
{
    luaL_Reg reg[] = {
        { "getHeight",     GetHeight },
        { "getWidth",      GetWidth  },
        { 0, 0 }
    };

    return Luax::RegisterType(L, &love::Font::type, reg, nullptr);
}

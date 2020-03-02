#pragma once

#include "objects/font/font.h"

namespace Wrap_Font
{
    int GetWidth(lua_State * L);

    int GetHeight(lua_State * L);

    love::Font * CheckFont(lua_State * L, int index);

    int Register(lua_State * L);
}

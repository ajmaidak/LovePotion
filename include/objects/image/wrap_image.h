#pragma once

#include "objects/image/image.h"

namespace Wrap_Image
{
    int New(lua_State * L);

    int GetDimensions(lua_State * L);

    int GetFilter(lua_State * L);

    int GetHeight(lua_State * L);

    int GetWidth(lua_State * L);

    int GetWrap(lua_State * L);

    int SetFilter(lua_State * L);

    int SetWrap(lua_State * L);

    Image * CheckImage(lua_State * L, int index);

    int Register(lua_State * L);
}

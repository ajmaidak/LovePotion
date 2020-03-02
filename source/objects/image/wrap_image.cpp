#include "common/runtime.h"
#include "objects/image/wrap_image.h"

using namespace love;

love::Type Image::type("Image", &Object::type);

int Wrap_Image::GetDimensions(lua_State * L)
{
    Image * self = Wrap_Image::CheckImage(L, 1);

    lua_pushnumber(L, self->GetWidth());
    lua_pushnumber(L, self->GetHeight());

    return 2;
}

int Wrap_Image::GetHeight(lua_State * L)
{
    Image * self = Wrap_Image::CheckImage(L, 1);

    lua_pushnumber(L, self->GetHeight());

    return 1;
}

int Wrap_Image::GetWidth(lua_State * L)
{
    Image * self = Wrap_Image::CheckImage(L, 1);

    lua_pushnumber(L, self->GetWidth());

    return 1;
}

Image * Wrap_Image::CheckImage(lua_State * L, int index)
{
    return Luax::CheckType<Image>(L, index);
}

int Wrap_Image::Register(lua_State * L)
{
    luaL_Reg reg[] = {
        { "getDimensions", GetDimensions },
        { "getHeight",     GetHeight     },
        { "getWidth",      GetWidth      },
        { 0, 0 }
    };

    return Luax::RegisterType(L, &Image::type, reg, nullptr);
}

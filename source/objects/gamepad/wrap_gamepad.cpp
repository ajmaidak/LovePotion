#include "common/runtime.h"
#include "objects/gamepad/wrap_gamepad.h"

#define CLASS_NAME "Gamepad"
#define CLASS_TYPE LUAOBJ_TYPE_GAMEPAD

int Wrap_Gamepad::New(lua_State * L)
{
    void * raw_self = luaobj_newudata(L, sizeof(Gamepad));

    luaobj_setclass(L, CLASS_TYPE, CLASS_NAME);

    Gamepad * self = new (raw_self) Gamepad();

    Luax::RegisterObject(L, 2, self);

    return 0;
}

int Wrap_Gamepad::__ToString(lua_State * L)
{
    Gamepad * self = (Gamepad *)luaobj_checkudata(L, 1, CLASS_TYPE);

    std::string str = self->ToString();

    lua_pushstring(L, str.c_str());

    return 1;
}

int Wrap_Gamepad::Register(lua_State * L)
{
    luaL_Reg reg[] =
    {
        { "__tostring", __ToString },
        { 0, 0 },
    };

    luaobj_newclass(L, CLASS_NAME, NULL, NULL, reg);

    return 1;
}

#include "common/runtime.h"
#include "objects/gamepad/wrap_gamepad.h"

int Wrap_Gamepad::GetID(lua_State * L)
{
    Gamepad * self = Wrap_Gamepad::CheckJoystick(L, 1);

    lua_pushnumber(L, self->GetID());

    return 1;
}

int Wrap_Gamepad::IsGamepadDown(lua_State * L)
{
    Gamepad * self = Wrap_Gamepad::CheckJoystick(L, 1);

    std::string button = luaL_checkstring(L, 2);

    lua_pushboolean(L, self->IsGamepadDown(button));

    return 1;
}

int Wrap_Gamepad::IsDown(lua_State * L)
{
    Gamepad * self = Wrap_Gamepad::CheckJoystick(L, 1);

    size_t buttonCount = Input::GetButtons().size();
    size_t button = std::clamp((size_t)luaL_checkinteger(L, 2), (size_t)1, buttonCount);

    lua_pushboolean(L, self->IsDown(button));

    return 1;
}

Gamepad * Wrap_Gamepad::CheckJoystick(lua_State * L, int index)
{
    return Luax::CheckType<Gamepad>(L, index);
}

int Wrap_Gamepad::Register(lua_State * L)
{
    luaL_Reg reg[] =
    {
        { "getID",         GetID         },
        { "isDown",        IsDown        },
        { "isGamepadDown", IsGamepadDown },
        { 0,        0      }
    };

    return Luax::RegisterType(L, &Gamepad::type, reg, nullptr);
}

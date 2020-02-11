#include "common/runtime.h"
#include "modules/joystick.h"

void Joystick::Initialize()
{
    for (size_t index = 0; index < MAX_GAMEPADS; index++)
        Joystick::AddGamepad(new Gamepad(index));
}

Gamepad * Joystick::GetJoystickFromID(size_t index)
{
    if (index < 0 || index >= m_gamepads.size())
        return nullptr;

    return m_gamepads[index];
}

void Joystick::AddGamepad(Gamepad * gamepad)
{
    m_gamepads.emplace_back(gamepad);
}

int Joystick::GetJoystickCount(lua_State * L)
{
    size_t count = m_gamepads.size();

    lua_pushnumber(L, count);

    return 1;
}

int Joystick::GetJoysticks(lua_State * L)
{
    size_t size = m_gamepads.size();
    lua_createtable(L, size, 0);

    for (size_t i = 0; i < size; i++)
    {
        Gamepad * gamepad = GetJoystickFromID(i);

        Luax::PushType(L, gamepad);
        lua_rawseti(L, -2, i + 1);
    }

    return 1;
}

int Joystick::Register(lua_State * L)
{
    luaL_Reg reg[] =
    {
        { "getJoystickCount",   GetJoystickCount },
        { "getJoysticks",       GetJoysticks     },
        { 0,                    0                }
    };

    lua_CFunction types[] =
    {
        Wrap_Gamepad::Register,
        0
    };

    Joystick::Initialize();

    Module module;
    module.name = "joystick";
    module.functions = reg;
    module.types = types;

    return Luax::RegisterModule(L, module);
}

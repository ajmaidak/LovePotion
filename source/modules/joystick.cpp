#include "common/runtime.h"

#include "objects/gamepad/gamepad.h"
#include "objects/gamepad/wrap_gamepad.h"
#include "modules/joystick.h"

void Joystick::Initialize(lua_State * L)
{

}

Gamepad * Joystick::GetJoystickFromID(uint id)
{
    return controllers[id];
}

//Löve2D Functions

//Super hacky workaround for now..
//love.joystick.getJoysticks
int Joystick::GetJoysticks(lua_State * L)
{
    lua_newtable(L);

    for (uint i = 0; i < controllers.size(); i++)
    {
        lua_pushnumber(L, i + 1);
        love_push_userdata(L, controllers[i]);

        lua_settable(L, -3);
    }

    return 1;
}


//love.joystick.getJoystickCount
int Joystick::GetJoystickCount(lua_State * L)
{
    lua_pushnumber(L, controllers.size());

    return 1;
}

//End Löve2D Functions

void Joystick::AddJoystick(Gamepad * gamepad)
{
    controllers.push_back(gamepad);
}

void Joystick::RemoveJoystick(uint id)
{
    controllers.erase(controllers.begin() + id);
}

std::vector<Gamepad *> Joystick::GetJoysticks()
{
    return controllers;
}

int Joystick::Register(lua_State * L)
{
    #if defined (__SWITCH__)
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    #endif

    gamepadNew(L);
    
    luaL_Reg reg[] = 
    {
        { "getJoystickCount", GetJoystickCount },
        { "getJoysticks",     GetJoysticks     },
        { 0, 0 },
    };

    love_register_module(L, "love.joystick", reg);

    return 1;
}

#include "common/runtime.h"
#include "modules/event.h"

#include "modules/love.h"

//Löve2D Functions

int LoveEvent::Pump(lua_State * L)
{
    return 0;
}

//love.event.quit
int LoveEvent::Quit(lua_State * L)
{
    Love::Quit(L);

    return 0;
}

//End Löve2D Functions

bool LoveEvent::IsTouchDown()
{
    return m_touchDown;
}

int LoveEvent::Register(lua_State * L)
{
    luaL_Reg reg[] =
    {
        { "poll", Poll },
        { "pump", Pump },
        { "quit", Quit },
        { 0,      0    }
    };

    WrappedModule module;
    module.name = "event";
    module.functions = reg;

    return Luax::RegisterModule(L, module);
}

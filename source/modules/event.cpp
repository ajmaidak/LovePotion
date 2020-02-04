#include "common/runtime.h"
#include "common/input.h"

#include "modules/event.h"
#include "modules/love.h"

//Löve2D Functions

int LoveEvent::Pump(lua_State * L)
{
    while (Input::PollEvent(&m_event))
    {
        switch (m_event.type)
        {
            case LOVE_GAMEPADUP:
            case LOVE_GAMEPADDOWN:
            {
                const char * field = (m_event.type == LOVE_GAMEPADDOWN) ?
                        "gamepadpressed" : "gamepadreleased";

                // TODO: send it to love.event.poll

                break;
            }

            case LOVE_GAMEPADAXIS:
                break;

            case LOVE_TOUCHPRESS:
            case LOVE_TOUCHRELEASE:
            {
                const char * field = (m_event.type == LOVE_TOUCHPRESS) ?
                        "touchpressed" : "touchreleased";

                break;
            }

            default:
                break;
        }
    }

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

    Module module;
    module.name = "event";
    module.functions = reg;

    return Luax::RegisterModule(L, module);
}

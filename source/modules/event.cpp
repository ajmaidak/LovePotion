#include "common/runtime.h"
#include "common/input.h"

#include "modules/event.h"
#include "modules/love.h"

//Löve2D Functions
#include "wrap_Event_lua.h"

int LoveEvent::Pump(lua_State * L)
{
    while (Input::PollEvent(&m_event))
    {
        Message * message = nullptr;

        std::vector<Variant> vargs;
        vargs.reserve(4);

        switch (m_event.type)
        {
            case LOVE_GAMEPADUP:
            case LOVE_GAMEPADDOWN:
            {
                std::string field = (m_event.type == LOVE_GAMEPADDOWN) ?
                        "gamepadpressed" : "gamepadreleased";

                vargs.emplace_back(Variant("System", strlen("System")));
                vargs.emplace_back(Variant(m_event.button.name));

                message = new Message(field, vargs);

                break;
            }

            case LOVE_GAMEPADAXIS:
                break;

            case LOVE_TOUCHPRESS:
            case LOVE_TOUCHRELEASE:
            {
                const char * field = (m_event.type == LOVE_TOUCHPRESS) ?
                         "touchpressed" : "touchreleased";

                // args.push_back(Variant(1.0f));
                // args.push_back(Variant((float)m_event.touch.x));
                // args.push_back(Variant((float)m_event.touch.y));

                // m_queue.push(new Message(field, args));

                break;
            }

            default:
                break;
        }

        if (message)
            m_queue.push(message);

    }

    return 0;
}

bool LoveEvent::Poll(Message *& message)
{
    if (m_queue.empty())
        return false;

    message = m_queue.front();
    m_queue.pop();

    return true;
};

int LoveEvent::Poll_I(lua_State * L)
{
    Message * message = nullptr;

    if (LoveEvent::Poll(message))
    {
        int args = message->ToLua(L);
        delete message;

        return args;
    }

    return 0;
}

//love.event.quit
int LoveEvent::Quit(lua_State * L)
{
    std::vector<Variant> args = {Variant::FromLua(L, 1)};
    m_queue.push(new Message("quit", args));

    lua_pushboolean(L, true);

    return 1;
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
        { "poll_i", Poll_I },
        { "pump",   Pump   },
        { "quit",   Quit   },
        { 0,        0      }
    };

    Module module;
    module.name = "event";
    module.functions = reg;

    int ret = Luax::RegisterModule(L, module);

    if (luaL_loadbuffer(L, (const char *)wrap_event_lua, wrap_event_lua_size, "wrap_Event.lua") == 0)
        lua_call(L, 0, 0);
    else
        lua_error(L);

    return ret;
}

#include "common/runtime.h"
#include "modules/event/wrap_event.h"

#include "wrap_Event_lua.h"

#define instance() (Module::GetInstance<love::Event>(Module::M_EVENT))

int Wrap_Event::Poll_I(lua_State * L)
{
    Message * message = nullptr;

    if (instance()->Poll(message))
    {
        int args = message->ToLua(L);
        delete message;

        return args;
    }

    return 0;
}

int Wrap_Event::Clear(lua_State * L)
{
    Luax::CatchException(L, [&]() {
        instance()->Clear();
    });

    return 0;
}

int Wrap_Event::Quit(lua_State * L)
{
    Luax::CatchException(L, [&]() {
        std::vector<Variant> args = {Variant::FromLua(L, 1)};

        StrongReference<Message> message(new Message("quit", args), Acquire::NORETAIN);

        instance()->Push(message);
    });

    lua_pushboolean(L, true);

    return 1;
}

int Wrap_Event::Pump(lua_State * L)
{
    Luax::CatchException(L, [&]() {
        instance()->Pump();
    });

    return 0;
}

int Wrap_Event::Register(lua_State * L)
{
    luaL_Reg reg[] =
    {
        { "poll_i", Poll_I },
        { "pump",   Pump   },
        { "quit",   Quit   },
        { 0,        0      }
    };

    Event * instance = instance();
    if (instance == nullptr)
        Luax::CatchException(L, [&]() { instance = new love::Event(); });
    else
        instance->Retain();

    WrappedModule module;

    module.instance = instance;
    module.name = "event";
    module.functions = reg;
    module.type = &Module::type;
    module.types = 0;

    int ret = Luax::RegisterModule(L, module);

    if (luaL_loadbuffer(L, (const char *)wrap_event_lua, wrap_event_lua_size, "wrap_Event.lua") == 0)
        lua_call(L, 0, 0);
    else
        lua_error(L);

    return ret;
}

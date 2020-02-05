#include "common/runtime.h"
#include "common/assets.h"

#include "modules/love.h"
#include "common/display.h"
#include "modules/timer.h"

enum DoneAction
{
    RESTART = 0,
    QUIT
};

DoneAction Run_Love_Potion(lua_State * L, int retval)
{
    int stackpos = lua_gettop(L);
    while (lua_resume(L, nullptr, 0) == LUA_YIELD)
            lua_pop(L, lua_gettop(L) - stackpos);

    return DoneAction::QUIT;
}

int main(int argc, char * argv[])
{
    Logger::Initialize(1);

    char * path = (argc == 2) ? argv[1] : argv[0];
    Assets::Initialize(path);

    Display::Initialize();

    // Make a new Lua state
    lua_State * L = luaL_newstate();
    luaL_openlibs(L);

    // preload love
    Love::Preload(L, Love::Initialize, "love");

    // require "love"
    lua_getglobal(L, "require");
    lua_pushstring(L, "love");
    lua_call(L, 1, 1);
    lua_pop(L, 1);

    // boot!
    lua_getglobal(L, "require");
    lua_pushstring(L, "love.boot");
    lua_call(L, 1, 1);

    lua_newthread(L);
    lua_pushvalue(L, -2);

    if (!Love::EnsureApplicationType(L))
        return 1;

    DoneAction done = DoneAction::QUIT;

    while (appletMainLoop())
    {
        done = Run_Love_Potion(L, 0);
        if (done == DoneAction::QUIT)
            break;
    }

    Love::Exit(L);

    return 0;
}

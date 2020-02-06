#include "common/runtime.h"
#include "common/assets.h"

#include "modules/love.h"
#include "common/backend/display.h"

DoneAction Run_Love_Potion(lua_State * L, int & retval)
{
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

    // put this on a new lua thread
    lua_newthread(L);
    lua_pushvalue(L, -2);

    /*
    ** get what's on the stack
    ** this will keep running until "quit"
    */
    int stackpos = lua_gettop(L);
    while (lua_resume(L, nullptr, 0) == LUA_YIELD)
            lua_pop(L, lua_gettop(L) - stackpos);

    // custom quit value
    if (lua_isnumber(L, -1))
        retval = (int)lua_tonumber(L, -1);

    // actually return quit
    return DoneAction::DONE_QUIT;
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

    DoneAction done = DoneAction::DONE_QUIT;
    int retval = 0;

    while (appletMainLoop())
    {
        done = Run_Love_Potion(L, retval);
        if (done == DoneAction::DONE_QUIT)
            break;
    }

    Love::Exit(L);

    return retval;
}

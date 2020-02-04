#include "common/runtime.h"
#include "common/assets.h"

#include "modules/love.h"
#include "common/display.h"
#include "modules/timer.h"

int main(int argc, char * argv[])
{
    Logger::Initialize(1);

    lua_State * L = luaL_newstate();
    luaL_openlibs(L);

    Love::Preload(L, Love::Initialize, "love");

    char * path = (argc == 2) ? argv[1] : argv[0];
    Assets::Initialize(path);

    Display::Initialize();

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

    while (appletMainLoop())
    {
        int stackpos = lua_gettop(L);
        while (lua_resume(L, nullptr, 0) == LUA_YIELD)
            lua_pop(L, lua_gettop(L) - stackpos);
    }

    Love::Exit(L);

    return 0;
}

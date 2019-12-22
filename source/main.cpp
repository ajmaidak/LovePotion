#include "common/runtime.h"
#include "common/assets.h"

#include "modules/love.h"
#include "common/display.h"

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

    Love::Boot(L);

    while (appletMainLoop())
    {
        if (Love::IsRunning())
           luaL_dostring(L, "xpcall(love.run, love.errorhandler)");
        else
            break;
    }

    Love::Exit(L);

    return 0;
}

#include "common/runtime.h"
#include "common/assets.h"

#include "modules/love.h"

int main(int argc, char * argv[])
{
    lua_State * L = luaL_newstate();

    luaL_openlibs(L);

    Love::Preload(L, luaopen_luautf8, "utf8");
    // love_preload(L, LuaSocket::InitSocket, "socket");
    // love_preload(L, LuaSocket::InitHTTP,   "socket.http");

    Logger::Initialize();

    char * path = (argc == 2) ? argv[1] : argv[0];
    Assets::Initialize(path);

    luaL_requiref(L, "love", Love::Initialize, true);
    lua_pop(L, -1);

    Love::InitializeConstants(L);

    // luaL_dobuffer(L, (char *)boot_lua, boot_lua_size, "boot");

    while (appletMainLoop())
    {
        if (Love::IsRunning())
            luaL_dostring(L, "xpcall(love.run, love.errhand");
        else
            break;
    }

    Love::Exit(L);

    Logger::Exit();

    return 0;
}

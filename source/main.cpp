#include "common/runtime.h"
#include "common/assets.h"

#include "modules/love.h"

#include "boot_lua.h"

#define luaL_dobuffer(L, b, n, s) \
    (luaL_loadbuffer(L, b, n, s) || lua_pcall(L, 0, LUA_MULTRET, 0))

int main(int argc, char * argv[])
{
    Logger::Initialize();

    lua_State * L = luaL_newstate();
    luaL_openlibs(L);

    Love::Preload(L, luaopen_luautf8, "utf8");
    // love_preload(L, LuaSocket::InitSocket, "socket");
    // love_preload(L, LuaSocket::InitHTTP,   "socket.http");

    char * path = (argc == 2) ? argv[1] : argv[0];
    Assets::Initialize(path);

    luaL_requiref(L, "love", Love::Initialize, true);
    lua_pop(L, -1);

    Love::InitializeConstants(L);

    luaL_dobuffer(L, (char *)boot_lua, boot_lua_size, "boot");

    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);

    printf("Hello World!\n");

    while (appletMainLoop())
    {
        /*if (Love::IsRunning())
            luaL_dostring(L, "xpcall(love.run, love.errhand");
        else
            break;*/

        // Flush and swap framebuffers
        gfxFlushBuffers();
        gfxSwapBuffers();

        //Wait for VBlank
        gspWaitForVBlank();
    }

    Love::Exit(L);

    return 0;
}

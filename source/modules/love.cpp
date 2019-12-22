#include "common/runtime.h"

#include "common/version.h"
#include "modules/love.h"

#include "common/display.h"

#include "modules/event.h"
#include "modules/filesystem.h"
#include "modules/graphics.h"
#include "modules/timer.h"
#include "modules/window.h"

/*
** @func Initialize
** Initializes the framework
*/
int Love::Initialize(lua_State * L)
{
    m_modules =
    {{
        { "event",      LoveEvent::Register,  NULL          },
        { "graphics",   Graphics::Register,   NULL          },
        { "filesystem", Filesystem::Register, NULL          },
        { "timer",      Timer::Register,      NULL          },
        { "window",     Window::Register,     Display::Exit },
        { 0 }
    }};

    // preload all the modules
    char modname[30];
    for (int i = 0; m_modules[i].name; i++)
    {
        strcpy(modname, "love.");
        strcat(modname, m_modules[i].name);
        Love::Preload(L, m_modules[i].reg, modname);
    }

    luaL_Reg reg[] =
    {
        //{ "_nogame",       NULL     },
        { "getVersion",    GetVersion   },
        { "run",           Run          },
        { "quit",          Quit         },
        { 0 }
    };

    luaL_newlib(L, reg);

    return 1;
}

/*
** @func InitializeConstants
** Initialize various constants.
** Mostly for compatability purposes.
*/
void Love::InitializeConstants(lua_State * L)
{
    lua_getglobal(L, "love");

    lua_newtable(L);

    // love._os = "Horizon"
    lua_pushstring(L, "Horizon");
    lua_setfield(L, -2, "_os");

    //love._console_name
    lua_pushstring(L, LOVE_POTION_CONSOLE);
    lua_setfield(L, -2, "_console_name");

    //love._potion_version
    lua_pushstring(L, Version::LOVE_POTION);
    lua_setfield(L, -2, "_potion_version");

    // love._version
    lua_pushstring(L, Version::LOVE);
    lua_setfield(L, -2, "_version");

    // love._(major, minor, revision, codename)
    lua_pushnumber(L, Version::MAJOR);
    lua_setfield(L, -2, "_version_major");

    lua_pushnumber(L, Version::MINOR);
    lua_setfield(L, -2, "_version_minor");

    lua_pushnumber(L, Version::REVISION);
    lua_setfield(L, -2, "_version_revision");

    lua_pushstring(L, Version::CODENAME);
    lua_setfield(L, -2, "_version_codename");

    lua_pop(L, 1);
}

/*
** @func Run
** Runs the framework's main loop
** Timer step, update, draw
**
** TO DO: commonize display drawing
** how? who knows, it'll be hard
*/
int Love::Run(lua_State * L)
{
    luaL_dostring(L, LOVE_TIMER_STEP);

    if (luaL_dostring(L, LOVE_UPDATE))
        luaL_error(L, "%s", lua_tostring(L, -1));

    if (Display::Draw(L))
        luaL_error(L, "%s", lua_tostring(L, -1));

    Timer::Tick();

    return 0;
}

/*
** @func GetVersion
** Return the version for the framework.
*/
int Love::GetVersion(lua_State * L)
{
    lua_pushnumber(L, Version::MAJOR);
    lua_pushnumber(L, Version::MINOR);
    lua_pushnumber(L, Version::REVISION);
    lua_pushstring(L, Version::CODENAME);

    return 4;
}

/*
** @func IsRunning
** Checks if the framework is running.
** @ret boolean
** Is the framework running?
*/
bool Love::IsRunning()
{
    return m_quit == false;
}

/*
** @func Quit
** Quits the framework
*/
int Love::Quit(lua_State * L)
{
    m_quit = true;

    return 0;
}

//------------------------------//

/*
** @func GetField
** Gets a field from the love module.
** May return nil if it does not exist on the Lua stack.
*/
void Love::GetField(lua_State * L, const char * field)
{
    lua_getfield(L, LUA_GLOBALSINDEX, "love");
    lua_getfield(L, -1, field);
    lua_remove(L, -2);
}

/*
** @func Preload
** Preloads a Lua C function <func> into package.preload
** with <name>. See the Lua 5.1 manual for more details:
** https://www.lua.org/manual/5.1/manual.html#pdf-package.preload
*/
int Love::Preload(lua_State * L, lua_CFunction func, const char * name)
{
    lua_getglobal(L, "package");
    lua_getfield(L, -1, "preload");
    lua_pushcfunction(L, func);
    lua_setfield(L, -2, name);
    lua_pop(L, 2);

    return 0;
}

/*
** @func GetRegistry
** Gets the field for the Lua registry index <registry>.
** This is necessary to store userdata and push it later.
*/
int Love::GetRegistry(lua_State * L, int registry)
{
    switch (registry)
    {
        case 0:
            lua_getfield(L, LUA_REGISTRYINDEX, "_loveobjects");
            return 1;
        default:
            return luaL_error(L, "Attempted to use invalid registry");
    }
}

/*
** @func DeRegObject
** De-register a pointer to <object> in the Registry
** given its light userdata key.
*/
void Love::DeRegObject(lua_State * L, void * object)
{
    Love::GetRegistry(L, 0);

    lua_pushlightuserdata(L, object);
    lua_pushnil(L);
    lua_settable(L, -3);

    lua_setfield(L, LUA_REGISTRYINDEX, "_loveobjects");
}

/*
** @func RegObject
** Register a pointer to <object> in the Registry
** given the index of it on the stack and its light userdata key.
*/
void Love::RegObject(lua_State * L, int index, void * object)
{
    Love::GetRegistry(L, 0);

    lua_pushlightuserdata(L, object);
    lua_pushvalue(L, index);
    lua_settable(L, -3);

    lua_setfield(L, LUA_REGISTRYINDEX, "_loveobjects");
}

//------------------------------//

/*
** @func Exit
** Called when the application is shutting down
** and cleans up everything.
*/
void Love::Exit(lua_State * L)
{
    for (int i = 0; m_modules[i].name; i++)
    {
        if (m_modules[i].close)
            m_modules[i].close();
    }

    lua_close(L);

    Logger::Exit();
}

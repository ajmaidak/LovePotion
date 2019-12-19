#pragma once

extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>

    #include <compat-5.3.h>
    #include <luaobj.h>

    #include <lutf8lib.h>
}

#include <SDL.h>
#include <SDL_mixer.h>
#include <curl/curl.h>

#if defined (_3DS)
    #include "common/defines.h"
#elif defined (__SWITCH__)
    #include "common/defines.h"
#endif

#include "common/logger.h"
#include "common/aux.h"

// std stuff
#include <string>
#include <math.h>
#include <array>

#define LOVE_TIMER_STEP "if love.timer then love.timer.step() end"
#define LOVE_UPDATE "if love.update then love.update(love.timer.getDelta()) end"

typedef struct {
    const char * name;
    int (* reg)(lua_State * L);
    void (* close)(void);
} love_modules;

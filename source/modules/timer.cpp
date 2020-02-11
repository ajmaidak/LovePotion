#include "common/runtime.h"
#include "modules/timer.h"

#include <SDL.h>

//Löve2D Functions

//love.timer.getFPS
int Timer::GetFPS(lua_State * L)
{
    lua_pushnumber(L, round(m_totalFrames));

    return 1;
}

//love.timer.getTime
int Timer::GetTime(lua_State * L)
{
    u32 time = SDL_GetTicks();
    lua_pushnumber(L, time * 0.001f);

    return 1;
}

//love.timer.getDelta
int Timer::GetDelta(lua_State * L)
{
    lua_pushnumber(L, m_deltatime);

    return 1;
}

//love.timer.step
int Timer::Step(lua_State * L)
{
    m_frames++;

    m_lastTime = m_currentTime;

    m_currentTime = SDL_GetTicks();

    m_deltatime = (m_currentTime - m_lastTime) * 0.001f;

    if (m_deltatime < 0)
        m_deltatime = 0;

    // FPS CALCULATION

    float delta = SDL_GetTicks() - m_lastCountTime;

    if (delta >= 1000.0f)
    {
        m_totalFrames = (m_frames / delta) * 1000.0f;
        m_frames = 0;
        m_lastCountTime = SDL_GetTicks();
    }

    return 0;
}

//love.timer.sleep
int Timer::Sleep(lua_State * L)
{
    float duration = luaL_checknumber(L, 1);
    u32 sleepDuration = (duration * 1000.0f);

    //svcSleepThread(1000000ULL * sleepDuration);
    SDL_Delay(sleepDuration);

    return 0;
}

//End Löve2D Functions

float Timer::GetDelta()
{
    return m_deltatime;
}

int Timer::Register(lua_State * L)
{
    luaL_Reg reg[] =
    {
        { "getDelta", GetDelta },
        { "getFPS",   GetFPS   },
        { "getTime",  GetTime  },
        { "sleep",    Sleep    },
        { "step",     Step     },
        { 0,          0        }
    };

    Module module;
    module.name = "timer";
    module.functions = reg;
    module.types = 0;

    return Luax::RegisterModule(L, module);
}

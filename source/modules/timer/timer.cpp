#include "common/runtime.h"
#include "modules/timer/timer.h"

using namespace love;

#include <SDL.h>

//Löve2D Functions

#define SLEEP_ULL 1000000000ULL

Timer::Timer() : currentTime(0),
                 prevFPSUpdate(0),
                 fps(0),
                 averageDelta(0),
                 fpsUpdateFrequency(1),
                 frames(0),
                 dt(0)
{
    this->prevFPSUpdate = currentTime = this->GetTime();
}

float Timer::GetAverageDelta()
{
    return this->averageDelta;
}

float Timer::GetDelta()
{
    return this->dt;
}

int Timer::GetFPS()
{
    return this->fps;
}

double Timer::GetTime()
{
    return SDL_GetTicks();
}

void Timer::Sleep(s64 seconds)
{
    if (seconds >= 0)
        svcSleepThread(seconds * SLEEP_ULL);
}

double Timer::Step()
{
    this->lastTime = this->currentTime;
    this->currentTime = SDL_GetTicks();

    this->dt = (this->currentTime - this->lastTime) * 0.001;

    if (this->dt < 0)
        this->dt = 0;

    this->frames++;
    double timeSinceLast = this->currentTime - this->prevFPSUpdate;

    if (timeSinceLast > 1000)
    {
        this->fps = int((this->frames / timeSinceLast) * 1000);
        this->averageDelta = timeSinceLast / frames;
        this->prevFPSUpdate = this->currentTime;
        this->frames = 0;

        LOG("FPS %d - Delta %.1f", fps, this->dt);
    }

    return this->dt;
}

#include "common/runtime.h"
#include "modules/timer/timer.h"

#include <SDL.h>

//Löve2D Functions

#define CLOCK_DIV 1000000000.0

Timer::Timer() : currentTime(0),
                 prevFPSUpdate(0),
                 fps(0),
                 averageDelta(0),
                 fpsUpdateFrequency(1),
                 frames(0),
                 dt(0)
{}

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
    clockid_t clk_id = CLOCK_MONOTONIC;
    timespec time;
    double mt;

    if (clock_gettime(clk_id, &time) == 0)
        mt = (double)time.tv_sec + (double)time.tv_nsec / CLOCK_DIV;
    else
        mt = GetTimeOfDay();

    return mt;
}

void Timer::Sleep(float ms)
{
    SDL_Delay(ms);
}

double Timer::Step()
{
    this->frames++;
    this->lastTime = this->currentTime;

    this->currentTime = this->GetTime();

    this->dt = (this->currentTime - this->lastTime);

    double timeSinceLast = this->currentTime - 0;

    if (timeSinceLast > 1)
    {
        this->fps = int((this->frames / timeSinceLast) + 0.5);
        this->averageDelta = timeSinceLast / frames;
        this->prevFPSUpdate = this->currentTime;
        this->frames = 0;
    }

    return this->dt;
}

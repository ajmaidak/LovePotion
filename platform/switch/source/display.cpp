#include "common/runtime.h"
#include "common/display.h"

#include <SDL.h>

void Display::Initialize()
{
    if (m_open)
        return;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return;

    m_window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_FULLSCREEN);

    if (!m_window)
        return SDL_Quit();

    u32 HW_ACCEL = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    m_targets = {
        SDL_CreateRenderer(m_window, 0, HW_ACCEL)
    };

    if (!m_targets[0])
        return SDL_Quit();

    SDL_SetRenderDrawBlendMode(m_targets[0], SDL_BLENDMODE_BLEND);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
}

Renderer * Display::GetRenderer()
{
    return m_targets[0];
}

void Display::Clear(Color * color)
{
    //SDL_SetRenderDrawColor(Display::GetRenderer(), color->r, color->g, color->b, color->a);
    //SDL_RenderClear(Display::GetRenderer());

    //SDL_SetRenderDrawColor(Display::GetRenderer(), drawColor.r, drawColor.g, drawColor.b, drawColor.a);
}

int Display::Draw(lua_State * L)
{
    return 0;
}

void Display::Present()
{

}

std::vector<std::pair<int, int>> Display::GetWindowSizes()
{
    return std::vector<std::pair<int, int>> {
        { 1280, 720 },
    };
}

unsigned int Display::GetDisplayCount()
{
    return 1;
}

bool Display::IsOpen()
{
    return m_open;
}

void Display::Exit()
{
    if (m_targets[0])
        SDL_DestroyRenderer(m_targets[0]);

    if (m_window)
        SDL_DestroyWindow(m_window);

    SDL_Quit();
}

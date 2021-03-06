#include "common/runtime.h"
#include "modules/window/window.h"

using namespace love;

#include <SDL.h>
#include "common/exception.h"

Window::Window() : window(nullptr),
                   open(false)

{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw love::Exception("Could not initialize SDL video subsystem (%s)", SDL_GetError());

    this->displaySizes =
    {
        {1280, 720}
    };

    this->targets.reserve(1);
}

Window::~Window()
{
    if (this->targets.back())
        SDL_DestroyRenderer(this->targets.back());

    if (this->window)
        SDL_DestroyWindow(this->window);

    SDL_QuitSubSystem(SDL_INIT_VIDEO);

    this->open = false;
}

Renderer * Window::GetRenderer()
{
    return this->targets.back();
}

void Window::SetScreen(size_t screen)
{}

bool Window::SetMode()
{
    this->window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_FULLSCREEN);

    if (!this->window)
        return false;

    u32 HW_ACCEL = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

    this->targets.push_back(SDL_CreateRenderer(this->window, 0, HW_ACCEL));

    if (!this->targets.back())
        return false;

    SDL_SetRenderDrawBlendMode(this->targets.back(), SDL_BLENDMODE_BLEND);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    this->open = true;

    return true;
}

void Window::Clear(Color * color)
{
    // clear the background to the specified color
    SDL_SetRenderDrawColor(this->targets.back(), color->r, color->g, color->b, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(this->targets.back());

    auto foreground = this->graphics.Get()->GetColor();
    LOG("Foreground Color: {%.1f, %.1f, %.1f, %.1f}", foreground.r, foreground.g, foreground.b, foreground.a);
    SDL_SetRenderDrawColor(this->GetRenderer(), foreground.r, foreground.g, foreground.b, foreground.a);
}

void Window::SetGraphics(Graphics * g)
{
    this->graphics.Set(g);
}

void Window::Present()
{
    SDL_RenderPresent(this->targets.back());
}

std::vector<std::pair<int, int>> & Window::GetFullscreenModes()
{
    return this->displaySizes;
}

int Window::GetDisplayCount()
{
    return 1;
}

bool Window::IsOpen()
{
    return this->open;
}

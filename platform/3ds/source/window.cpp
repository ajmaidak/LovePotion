#include "common/runtime.h"
#include "modules/window/window.h"

std::vector<std::pair<int, int>> Window::GetFullscreenModes()
{
    return std::vector<std::pair<int, int>>
    {
        { 400, 240 },
        { 400, 240 },
        { 320, 240}
    };
}

int Window::GetDisplayCount()
{
    return 3;
}

bool Window::IsOpen()
{
    return true;
}

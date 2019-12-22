#include "common/runtime.h"
#include "modules/graphics.h"

#include "common/display.h"

void Display::Initialize()
{
    if (m_open)
        return;

    gfxInitDefault();

    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();

    m_targets = {
        C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT),
        C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT),
        C2D_CreateScreenTarget(GFX_TOP, GFX_RIGHT)
    };

    m_open = true;
}

void Display::Clear(Color * color)
{
    for (size_t index = 0; index < m_targets.size(); index++)
    {
        if (!color)
            *color = { 0, 0, 0, 1 };

        C2D_TargetClear(m_targets[index], C2D_Color32f(color->r, color->g, color->b, 1.0));
    }
}

int Display::Draw(lua_State * L)
{
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

    Color color = Graphics::GetBackgroundColor();

    for (size_t index = 0; index < m_targets.size(); index++)
    {
        if (!gfxIs3D() && index == 2)
            continue;

        C2D_TargetClear(m_targets[index], C2D_Color32f(color.r, color.g, color.b, 1.0));
        C2D_SceneBegin(m_targets[index]);

        //int display = std::clamp((int)index + 1, 1, 2);
        if (luaL_dostring(L, LOVE_DRAW))
            return 1;
    }

    C3D_FrameEnd(0);

    return 0;
}

std::vector<std::pair<int, int>> Display::GetWindowSizes()
{
    return std::vector<std::pair<int, int>> {
        { 400, 240 },
        { 320, 240}
    };
}

unsigned int Display::GetDisplayCount()
{
    return 2;
}

bool Display::IsOpen()
{
    return m_open;
}

void Display::Exit()
{
    C2D_Fini();
    C3D_Fini();
    gfxExit();
}

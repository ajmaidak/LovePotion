#include "common/runtime.h"
#include "modules/graphics.h"

#include "common/display.h"
#include "modules/love.h"

void Display::Initialize()
{
    if (m_open)
        return;

    gfxInitDefault();

    if (!C3D_Init(C3D_DEFAULT_CMDBUF_SIZE))
        svcBreak(USERBREAK_PANIC);

    if (!C2D_Init(C2D_DEFAULT_MAX_OBJECTS))
        svcBreak(USERBREAK_PANIC);

    C2D_Prepare();

    m_targets = {
        C2D_CreateScreenTarget(GFX_TOP,    GFX_LEFT),
        C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT),
        C2D_CreateScreenTarget(GFX_TOP,    GFX_RIGHT)
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
    if (!m_open)
        return 0;

    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

    Color color = Graphics::GetBackgroundColor();

    for (size_t index = 0; index < m_targets.size(); index++)
    {
        if (!gfxIs3D() && index == 2)
            continue;

        C2D_TargetClear(m_targets[index], C2D_Color32f(color.r, color.g, color.b, 1.0));
        C2D_SceneBegin(m_targets[index]);

        int display = std::clamp((int)index + 1, 1, 2);

        Love::GetField(L, "draw");
        if (!lua_isnoneornil(L, -1))
        {
            lua_pushstring(L, (display == 1) ? "top" : "bottom");
            int error = lua_pcall(L, 1, 0, 0);

            if (error != 0)
                return lua_error(L);
        }
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
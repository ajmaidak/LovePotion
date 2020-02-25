#include "common/runtime.h"
#include "common/backend/render.h"

void Render::Rectangle(const std::string & mode, float x, float y, float width, float height, const Color & color)
{
    u32 color32 = C2D_Color32f(color.r, color.g, color.b, color.a);

    if (mode == "fill")
        C2D_DrawRectSolid(x, y, 0.5, width, height, color32);
    else if (mode == "line")
    {
        // TOP
        C2D_DrawRectSolid(x, y, 0.5, width - 1, 1, color32);

        // RIGHT
        C2D_DrawRectSolid(x + width, y + 1, 0.5, 1, height - 1, color32);

        // BOTTOM
        C2D_DrawRectSolid(x, y + height, 0.5, width - 1, 1, color32);

        // LEFT
        C2D_DrawRectSolid(x, (y + 1), 0.5, 1, height - 1, color32);
    }
}

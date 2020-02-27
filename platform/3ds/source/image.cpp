#include "common/runtime.h"
#include "objects/image/image.h"

using namespace love;

Image::Image(const std::string & path)
{
    size_t pos = path.find_last_of(".") + 1;
    std::string translation;

    if (pos != std::string::npos)
        translation = (path.substr(0, pos) + "t3x");

    const char * realPath = translation.c_str();

    C2D_SpriteSheet sheet = C2D_SpriteSheetLoad(realPath);
    this->texture = C2D_SpriteSheetGetImage(sheet, 0);

    this->width = this->texture.subtex->width;
    this->height = this->texture.subtex->height;
}

void Image::Draw(float x, float y, float r, float sx, float sy)
{
    C2D_DrawParams params;

    params.depth = 0.5f;
    params.pos = {x, y, sx * this->width, sy * this->height};
    params.angle = r;

    // C2D_ImageTint tint;
    // Color color = Display::GetBlendColor();

    // u32 blend = C2D_Color32f(color.r, color.g, color.b, color.a);
    // C2D_PlainImageTint(&tint, blend, 1);

    C2D_DrawImage(this->texture, &params, NULL);
}

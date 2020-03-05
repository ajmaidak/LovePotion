#include "common/runtime.h"
#include "objects/image/image.h"

using namespace love;

Image::Image(const std::string & path)
{
    size_t pos = path.find_last_of(".") + 1;
    std::string translation;

    if (pos != std::string::npos)
        translation = (path.substr(0, pos) + "t3x");

    if (std::filesystem::exists(translation))
    {
        C2D_SpriteSheet sheet = C2D_SpriteSheetLoad(translation.c_str());
        this->texture = C2D_SpriteSheetGetImage(sheet, 0);

        this->width = this->texture.subtex->width;
        this->height = this->texture.subtex->height;
    }
}

void Image::Draw(float x, float y, float r, float scalarX, float scalarY, const Color & color)
{
    C2D_DrawParams params;

    params.depth = 0.5f;
    params.pos =
    {
        x, y,
        scalarX * this->width, scalarY * this->height
    };
    params.angle = r;

    C2D_ImageTint tint;
    C2D_AlphaImageTint(&tint, color.a);

    C2D_DrawImage(this->texture, &params, &tint);
}

#include "common/runtime.h"
#include "objects/font/font.h"

using namespace love;

Font::Font(const std::string & path, float size) : buffer(C2D_TextBufNew(4096)),
                                                   size(size)
{
    this->font = this->LoadFromPath(path);
}

Font::Font(float size) : buffer(C2D_TextBufNew(4096)),
                         size(size)
{
    this->font = this->LoadFromPath("standard");
}

Font::~Font()
{
    C2D_TextBufDelete(this->buffer);
    C2D_FontFree(this->font);
}

FontHandle Font::LoadFromPath(const std::string & path)
{
    if (path == "standard")
        return C2D_FontLoadSystem(CFG_REGION_USA);
    else if (path == "korean")
        return C2D_FontLoadSystem(CFG_REGION_KOR);
    else if (path == "taiwanese")
        return C2D_FontLoadSystem(CFG_REGION_TWN);
    else if (path == "chinese")
        return C2D_FontLoadSystem(CFG_REGION_CHN);

    size_t pos = path.find_last_of(".") + 1;
    std::string translation;

    if (pos != std::string::npos)
        translation = (path.substr(0, pos) + "fnt");

    if (std::filesystem::exists(translation))
        return C2D_FontLoad(translation.c_str());

    return NULL;
}

void Font::Print(const char * string, const DrawArgs & args, float * limit, const Color & color)
{
    C2D_TextBufClear(this->buffer);
    C2D_TextFontParse(&this->text, this->font, this->buffer, string);
    C2D_TextOptimize(&this->text);

    C2D_DrawText(&this->text, C2D_WithColor, args.x, args.y, 0.5, this->GetScale() * args.scalarX, this->GetScale() * args.scalarY, C2D_Color32f(color.r, color.g, color.b, color.a));
}

float Font::GetWidth(const char * text)
{
    float width = 0;
    C2D_Text measureText;
    C2D_TextBuf measureBuffer = C2D_TextBufNew(strlen(text));

    C2D_TextFontParse(&measureText, this->font, measureBuffer, text);

    if (strlen(text) != 0)
        C2D_TextGetDimensions(&measureText, this->GetScale(), this->GetScale(), &width, NULL);

    C2D_TextBufDelete(measureBuffer);

    return width;
}

float Font::GetHeight()
{
    return 30 * this->GetScale();
}

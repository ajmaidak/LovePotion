#include "common/runtime.h"
#include "modules/graphics/graphics.h"

using namespace love;

Graphics::Graphics() : backgroundColor({0, 0, 0, 0}),
                       foregroundColor({1, 1, 1, 1})
{}

Color Graphics::GetColor()
{
    return this->foregroundColor;
}

void Graphics::SetColor(const Color & color)
{
    AdjustColor(color, &this->foregroundColor);
}

Color Graphics::GetBackgroundColor()
{
    return this->backgroundColor;
}

void Graphics::SetBackgroundColor(const Color & color)
{
    AdjustColor(color, &this->backgroundColor);
}

void Graphics::AdjustColor(const Color & in, Color * out)
{
    float mul = 255.0f;

    #if defined(_3DS)
        mul = 1.0f;
    #endif

    out->r = std::clamp(in.r, 0.0f, 1.0f) * mul;
    out->g = std::clamp(in.g, 0.0f, 1.0f) * mul;
    out->b = std::clamp(in.b, 0.0f, 1.0f) * mul;
    out->a = std::clamp(in.a, 0.0f, 1.0f) * mul;
}

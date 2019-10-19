#include "common/runtime.h"
#include "objects/quad/quad.h"

Quad::Quad(int x, int y, int width, int height, int atlasWidth, int atlasHeight) : Object("Quad")
{
    this->view.x = x;
    this->view.y = y;

    this->view.width = width;
    this->view.height = height;

    this->view.atlasWidth = atlasWidth;
    this->view.atlasHeight = atlasHeight;
}

void Quad::SetViewport(int x, int y, int width, int height)
{
    this->view.x = x;
    this->view.y = y;

    this->view.width = width;
    this->view.height = height;
}

void Quad::SetViewport(int x, int y, int width, int height, int atlasWidth, int atlasHeight)
{
    this->view.x = x;
    this->view.y = y;

    this->view.width = width;
    this->view.height = height;

    this->view.atlasWidth = atlasWidth;
    this->view.atlasHeight = atlasHeight;

    #if defined(_3DS)
        this->FillSubTextureData();
    #endif
}

Viewport Quad::GetViewport()
{
    return this->view;
}

#if defined(_3DS)
void Quad::FillSubTextureData()
{
    float w_pow2 = (float)NextPO2(this->view.atlasWidth);
    float h_pow2 = (float)NextPO2(this->view.atlasHeight);

    float u0 = (float)this->view.x/w_pow2;
    float v0 = (float)this->view.y/h_pow2;

    float u1 = (float)(this->view.x + this->view.width)/w_pow2;
    float v1 = (float)(this->view.y + this->view.height)/h_pow2;

    this->subTexture.top     = 1.0f - v0;
    this->subTexture.left    = u0;
    this->subTexture.right   = u1;
    this->subTexture.bottom  = 1.0f - v1;

    this->subTexture.width   = this->view.width;
    this->subTexture.height  = this->view.height;
}

Tex3DS_SubTexture * Quad::GetSubTexture()
{
    return &this->subTexture;
}
#endif

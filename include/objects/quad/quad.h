#pragma once

class Quad : public Object
{
    public:
        Quad() {};
        Quad(int x, int y, int width, int height, int atlasWidth, int atlasHeight);

        Viewport GetViewport();
        void SetViewport(int x, int y, int width, int height);
        void SetViewport(int x, int y, int width, int height, int atlasWidth, int atlasHeight);

        #if defined(_3DS)
            void FillSubTextureData();
            Tex3DS_SubTexture * GetSubTexture();
        #endif

    private:
        Viewport view;
        #if defined(_3DS)
            Tex3DS_SubTexture subTexture;
        #endif
};

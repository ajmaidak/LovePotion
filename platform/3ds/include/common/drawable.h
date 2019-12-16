#pragma once

class Drawable : public Object
{
    public:
        Drawable(const std::string & type);
        Drawable() {};
        void Draw(float x, float y, float rotation, float scalarX, float scalarY, Color color);

        int GetWidth();
        int GetHeight();

        Tex3DS_SubTexture GetSubTexture();
        void SetSubTexture(const Tex3DS_SubTexture * subTexture);

    protected:
        int width;
        int height;

        C2D_Image image;
        Tex3DS_SubTexture subTexture;
        C2D_ImageTint imageTint;
};

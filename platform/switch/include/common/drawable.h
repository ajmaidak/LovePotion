#pragma once

class Drawable : public Object
{
    public:
        Drawable(const std::string & type);
        Drawable() {};
        ~Drawable();

        void Draw(SDL_Texture * texture, Viewport viewport, double x, double y, double rotation, double offsetX, double offsetY, double scalarX, double scalarY, SDL_Color color);

        int GetWidth();
        int GetHeight();
        
        void SetFilter();

        Viewport GetViewport();

    protected:
        void Flip(double scalarX, double scalarY);

        int width;
        int height;

        SDL_Texture * texture;

        Viewport viewport;

        SDL_RendererFlip flip;
};

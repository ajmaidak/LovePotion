#pragma once

#include "objects/image/image.h"
#include "objects/quad/quad.h"

#if defined(_3DS)
#   define MAX_SPRITES 250
#elif defined(__SWITCH__)
#   define MAX_SPRITES 1000
#else
#   define MAX_SPRITES 500
#endif

enum SpriteBatchUsage {
    SB_dynamic,
    SB_static,
    SB_stream
};

typedef struct {
    Quad * quad;
    float x, y, r, sx, sy, ox, oy;
} BatchSprite;

class SpriteBatch : public Object
{
    public:
        SpriteBatch(Image * texture, u16 maxsprites, SpriteBatchUsage usage);
        ~SpriteBatch();

        u16 Add(BatchSprite sprite);
        void clear();
        void flush();
        u16 GetBufferSize();
        Color GetColor();
        u16 GetCount();
        Image * GetTexture();
        void Set(u16 idx, BatchSprite sprite);
        void SetColor(Color color);
        void SetDrawRange();
        void SetDrawRange(u16 start, u16 count);
        void SetTexture(Image * texture);

        void Draw();

    private:
        Image * texture;
        u16 maxsprites;
        SpriteBatchUsage usage;

        std::vector<BatchSprite> sprites;
};

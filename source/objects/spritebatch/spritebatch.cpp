#include "common/runtime.h"

#include "objects/spritebatch/spritebatch.h"
#include "modules/graphics.h"

SpriteBatch::SpriteBatch(Image * texture, u16 maxsprites, SpriteBatchUsage usage) : Object("SpriteBatch")
{
    this->texture = texture;
    this->maxsprites = maxsprites;
    this->usage = usage;

    this->sprites = std::vector<BatchSprite>(maxsprites);
}

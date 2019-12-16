#include "common/runtime.h"

#include "objects/spritebatch/spritebatch.h"
#include "objects/spritebatch/wrap_spritebatch.h"

#define CLASS_TYPE LUAOBJ_TYPE_SPRITEBATCH
#define CLASS_NAME "SpriteBatch"

int spritebatchNew(lua_State * L)
{
    Image * texture = (Image *)luaobj_checkudata(L, 1, LUAOBJ_TYPE_IMAGE);

    u16 maxsprites = luaL_optinteger(L, 2, MAX_SPRITES);

    // get usage (currently unimplemented)

    void * raw_self = luaobj_newudata(L, sizeof(SpriteBatch));

    luaobj_setclass(L, CLASS_TYPE, CLASS_NAME);

    new (raw_self) SpriteBatch(texture, maxsprites, SpriteBatchUsage::SB_dynamic);

    return 1;
}

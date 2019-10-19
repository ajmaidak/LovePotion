#include "common/runtime.h"
#include "objects/quad/quad.h"
#include "objects/quad/wrap_quad.h"

#define CLASS_NAME "Quad"
#define CLASS_TYPE LUAOBJ_TYPE_QUAD

int quadNew(lua_State * L)
{
    int x = luaL_checknumber(L, 1);
    int y = luaL_checknumber(L, 2);

    int width = luaL_checknumber(L, 3);
    int height = luaL_checknumber(L, 4);

    if (width <= 0) luaL_error(L, "Quad width must be greater than 0!");
    if (height <= 0) luaL_error(L, "Quad height must be greater than 0!");

    int atlasWidth = luaL_checknumber(L, 5);
    int atlasHeight = luaL_checknumber(L, 6);

    if (atlasWidth <= 0) luaL_error(L, "Texture width must be greater than 0!");
    if (atlasHeight <= 0) luaL_error(L, "Texture height must be greater than 0!");

    void * raw_self = luaobj_newudata(L, sizeof(Quad));

    luaobj_setclass(L, CLASS_TYPE, CLASS_NAME);

    new (raw_self) Quad(x, y, width, height, atlasWidth, atlasHeight);

    return 1;
}

int quadGetTextureDimensions(lua_State * L)
{
    Quad * self = (Quad *)luaobj_checkudata(L, 1, CLASS_TYPE);

    Viewport view = self->GetViewport();

    lua_pushnumber(L, view.atlasWidth);
    lua_pushnumber(L, view.atlasHeight);

    return 2;
}

int quadGetViewport(lua_State * L)
{
    Quad * self = (Quad *)luaobj_checkudata(L, 1, CLASS_TYPE);

    Viewport view = self->GetViewport();

    lua_pushnumber(L, view.x);
    lua_pushnumber(L, view.y);
    lua_pushnumber(L, view.width);
    lua_pushnumber(L, view.height);

    return 4;
}

int quadSetViewport(lua_State * L)
{
    Quad * self = (Quad *)luaobj_checkudata(L, 1, CLASS_TYPE);

    int x = luaL_checknumber(L, 2);
    int y = luaL_checknumber(L, 3);

    int width = luaL_checknumber(L, 4);
    int height = luaL_checknumber(L, 5);

    if (width <= 0) luaL_error(L, "Quad width must be greater than 0!");
    if (height <= 0) luaL_error(L, "Quad height must be greater than 0!");

    if (lua_isnoneornil(L, 6))
        self->SetViewport(x, y, width, height);
    else
    {
        int atlasWidth = luaL_checknumber(L, 5);
        int atlasHeight = luaL_checknumber(L, 6);

        if (atlasWidth <= 0) luaL_error(L, "Texture width must be greater than 0!");
        if (atlasHeight <= 0) luaL_error(L, "Texture height must be greater than 0!");

        self->SetViewport(x, y, width, height, atlasWidth, atlasHeight);
    }

    return 0;
}

int quadToString(lua_State * L)
{
    Quad * self = (Quad *)luaobj_checkudata(L, 1, CLASS_TYPE);

    char * data = self->ToString();

    lua_pushstring(L, data);

    free(data);

    return 1;
}

int quadGC(lua_State * L)
{
    Quad * self = (Quad *)luaobj_checkudata(L, 1, CLASS_TYPE);

    self->~Quad();

    return 0;
}

int initQuadClass(lua_State * L)
{
    luaL_Reg reg[] = {
        { "__gc",                 quadGC                   },
        { "__tostring",           quadToString             },
        { "getTextureDimensions", quadGetTextureDimensions },
        { "getViewport",          quadGetViewport          },
        { "new",                  quadNew                  },
        { "setViewport",          quadSetViewport          },
        { 0, 0 },
    };

    luaobj_newclass(L, CLASS_NAME, NULL, quadNew, reg);

    return 1;
}
#pragma once

int spritebatchNew(lua_State * L);

int spritebatchAdd(lua_State * L);

// int spritebatchAddLayer(lua_State * L);

// int spritebatchAttachAttribute(lua_State * L);

int spritebatchClear(lua_State * L);

// int spritebatchFlush(lua_State * L);

int spritebatchGetBufferSize(lua_State * L);

int spritebatchGetColor(lua_State * L);

int spritebatchGetCount(lua_State * L);

int spritebatchGetTexture(lua_State * L);

int spritebatchSet(lua_State * L);

int spritebatchSetColor(lua_State * L);

int spritebatchSetDrawRange(lua_State * L);

// int spritebatchSetLayer(lua_State * L);

int spritebatchSetTexture(lua_State * L);

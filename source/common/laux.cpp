#include "common/runtime.h"

/*
** @func DoBuffer
** Runs a specified Lua Buffer
*/
int Aux::DoBuffer(lua_State * L, const char * buffer, size_t size, const char * name)
{
    return (luaL_loadbuffer(L, buffer, size, name) || lua_pcall(L, 0, LUA_MULTRET, 0));
}

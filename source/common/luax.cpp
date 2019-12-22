#include "common/runtime.h"

/*
** @func DoBuffer
** Runs a specified Lua Buffer
*/
int Luax::DoBuffer(lua_State * L, const char * buffer, size_t size, const char * name)
{
    return (luaL_loadbuffer(L, buffer, size, name) || lua_pcall(L, 0, LUA_MULTRET, 0));
}

/*
** @func InsistGlobal
** Make sure @field is global
** See https://github.com/love2d/love/blob/master/src/common/runtime.cpp#L748
*/
int Luax::InsistGlobal(lua_State * L, const char * field)
{
	lua_getglobal(L, field);

	if (!lua_istable(L, -1))
	{
		lua_pop(L, 1); // Pop the non-table.
		lua_newtable(L);
		lua_pushvalue(L, -1);
		lua_setglobal(L, field);
	}

	return 1;
}

/*
** @func RegisterModule
** Registers @module as a proper table to LOVE
** See https://github.com/love2d/love/blob/master/src/common/runtime.cpp#L375
*/
int Luax::RegisterModule(lua_State * L, const WrappedModule & module)
{
    Luax::InsistGlobal(L, "love");

    lua_newtable(L);

	const luaL_reg * funcs = module.functions;
    for (; funcs->name != nullptr; funcs++)
    {
        lua_pushcfunction(L, funcs->func);
        lua_setfield(L, -2, funcs->name);
    }

    lua_pushvalue(L, -1);
    lua_setfield(L, -3, module.name);
    lua_remove(L, -2);

	return 1;
}

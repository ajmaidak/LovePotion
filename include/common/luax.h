/*
** common/aux.h
** @brief   : Auxillary Lua functions
*/

namespace Luax
{
    int DoBuffer(lua_State * L, const char * buffer, size_t size, const char * name);

    int InsistGlobal(lua_State * L, const char * field);

    int RegisterModule(lua_State * L, const Module & module);

    void RegisterObject(lua_State * L, int n, void * userdata);

    void PushObject(lua_State * L, void * object);

    int Traceback(lua_State * L);
};

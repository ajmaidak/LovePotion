/*
** common/aux.h
** @brief   : Auxillary Lua functions
*/

enum Registry
{
    OBJECTS = 0,
    UNKNOWN
};

#define MAX_LUAOBJ_KEY 0x20000000000000ULL

#include "objects/object.h"
#include "common/type.h"

namespace Luax
{
    int DoBuffer(lua_State * L, const char * buffer, size_t size, const char * name);

    int InsistGlobal(lua_State * L, const char * field);

    int Insist(lua_State * L, int index, const char * key);

    lua_State * InsistPinnedThread(lua_State * L);

    void SetFunctions(lua_State * L, const luaL_reg * l);

    int RegisterModule(lua_State * L, const Module & module);

    int RegisterType(lua_State * L, love::Type * object, ...);

    int GarbageCollect(lua_State * L);

    int ToString(lua_State * L);

    int Equal(lua_State * L);

    love::Type * Type(lua_State *L, int idx);

    int Type(lua_State * L);

    int TypeOf(lua_State * L);

    int Release(lua_State * L);

    void RawNewType(lua_State * L, love::Type & type, Object * object);

    lua_Number ComputerObjectKey(lua_State * L, Object * object);

    void PushType(lua_State * L, love::Type & type, Object * object);

    template <typename T>
    void PushType(lua_State * L, T * object)
    {
        PushType(L, T::type, object);
    }

    template <typename T>
    void PushType(lua_State * L, StrongReference<T> & object)
    {
        PushType(L, T::type, object);
    }

    int TypeErrror(lua_State * L, int narg, const char * name);

    /*
    ** @func CheckType<T>
    ** Checks if the value on the Lua stack @index is of @type
    ** See: https://github.com/love2d/love/blob/master/src/common/runtime.h#L528
    */
    template <typename T>
    T * CheckType(lua_State * L, int index, const love::Type & type)
    {
        // If not userdata, error out
        if (lua_type(L, index) != LUA_TUSERDATA)
        {
            const char * name = type.GetName();
            Luax::TypeErrror(L, index, name);
        }

        Proxy * proxy = (Proxy *)lua_touserdata(L, index);

        // Check that it has a type and matches input
        if (proxy->type == nullptr || !proxy->type->IsA(type))
        {
            const char * name = type.GetName();
            Luax::TypeErrror(L, index, name);
        }

        if (proxy->object == nullptr)
            luaL_error(L, "Cannot use object after it has been released.");

        return (T *)proxy->object;
    }

    template <typename T>
    T * CheckType(lua_State * L, int index)
    {
        return CheckType<T>(L, index, T::type);
    }

    int Traceback(lua_State * L);
};

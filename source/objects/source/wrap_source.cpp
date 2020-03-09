#include "common/runtime.h"
#include "objects/source/wrap_source.h"

using namespace love;

int Wrap_Source::Register(lua_State * L)
{
    luaL_Reg reg[] =
    {
        { 0, 0 }
    };

    return Luax::RegisterType(L, &Source::type, reg, nullptr);
}

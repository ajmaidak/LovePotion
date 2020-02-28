#include "common/runtime.h"
#include "modules/data/wrap_datamodule.h"

using namespace love;

love::data::ContainerType Wrap_DataModule::CheckContainerType(lua_State * L, int index)
{
    const char * string = luaL_checkstring(L, index);
    love::data::ContainerType type = love::data::CONTAINER_STRING;

    if (!DataModule::GetConstant(string, type))
        Luax::EnumError(L, "container type", DataModule::GetConstants(), string);

    return type;
}

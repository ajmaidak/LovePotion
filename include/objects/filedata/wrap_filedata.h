#pragma once

#include "objects/filedata/filedata.h"

namespace Wrap_FileData
{
    int Clone(lua_State * L);

    int GetFilename(lua_State * L);

    int GetExtension(lua_State * L);

    FileData * CheckFileData(lua_State * L, int index);

    int Register(lua_State * L);
}

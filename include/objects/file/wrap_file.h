#pragma once

#include "objects/file/file.h"
#include "modules/filesystem.h"

namespace Wrap_File
{
    int New(lua_State * L);

    int Open(lua_State * L);

    int Write(lua_State * L);

    int Flush(lua_State * L);

    int GetSize(lua_State * L);

    int IsOpen(lua_State * L);

    int GetMode(lua_State * L);

    int Close(lua_State * L);

    int Register(lua_State * L);
}

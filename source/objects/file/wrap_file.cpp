#include "common/runtime.h"
#include "objects/file/wrap_file.h"

int Wrap_File::Open(lua_State * L)
{
    File * self = Wrap_File::CheckFile(L, 1);
    const char * str = 0;
    File::Mode mode = File::Mode::CLOSED;

    str = luaL_checkstring(L, 2);
    if (!File::GetConstant(str, mode))
        luaL_error(L, "Invalid file open mode %s", str);

    if (mode != File::CLOSED)
    {
        if (!self->Open(mode))
            return luaL_error(L, "Could not open file.");
        else
        {
            lua_pushboolean(L, 1);
            return 1;
        }
    }

    lua_pushboolean(L, 0);

    return 1;
}

File * Wrap_File::CheckFile(lua_State * L, int index)
{
    return Luax::CheckType<File>(L, index);
}

int Wrap_File::Register(lua_State * L)
{
    luaL_Reg reg[] =
    {
        // { "close",      fileClose    },
        // { "flush",      fileFlush    },
        // { "getMode",    fileGetMode  },
        // { "getSize",    fileGetSize  },
        // { "isOpen",     fileIsOpen   },
        { "open",    Open           },
        // { "read",       fileRead     },
        // { "write",      fileWrite    },
        { 0,         0              }
    };

    return Luax::RegisterType(L, &File::type, reg, nullptr);
}

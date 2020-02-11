#include "common/runtime.h"
#include "objects/file/wrap_file.h"

int Wrap_File::New(lua_State * L)
{
    const char * path = luaL_checkstring(L, 1);
    std::string abspath = Filesystem::GetSaveDirectory() + std::string(path);

    const char * str = 0;
    File::Mode mode = File::CLOSED;

    if (lua_isstring(L, 2))
    {
        str = luaL_checkstring(L, 2);
        if (!File::GetConstant(str, mode))
            luaL_error(L, "Invalid file open mode %s", str);
    }

    File * file = new File(abspath.c_str());

    if (mode != File::CLOSED)
    {
        if (!file->Open(mode))
            return luaL_error(L, "Could not open file.");
    }

    Luax::PushType(L, file);

    file->Release();

    return 1;
}

int Wrap_File::Open(lua_State * L)
{
    File * self = (File *)Luax::CheckType<File>(L, 1);
    const char * str = 0;
    File::Mode mode = File::Mode::CLOSED;

    if (lua_isstring(L, 2))
    {
        str = luaL_checkstring(L, 2);
        if (!File::GetConstant(str, mode))
            luaL_error(L, "Invalid file open mode %s", str);
    }

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

int Wrap_File::Register(lua_State * L)
{
    luaL_Reg reg[] =
    {
        // { "close",      fileClose    },
        // { "flush",      fileFlush    },
        // { "getMode",    fileGetMode  },
        // { "getSize",    fileGetSize  },
        // { "isOpen",     fileIsOpen   },
        // { "new",        fileNew      },
        { "open",    Open           },
        // { "read",       fileRead     },
        // { "write",      fileWrite    },
        { 0,         0              }
    };

    return Luax::RegisterType(L, &File::type, reg, nullptr);
}

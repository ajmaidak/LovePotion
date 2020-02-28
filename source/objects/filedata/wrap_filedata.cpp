#include "common/runtime.h"
#include "objects/filedata/wrap_filedata.h"

using namespace love;

int Wrap_FileData::Clone(lua_State * L)
{
    FileData * data = Wrap_FileData::CheckFileData(L, 1);
    FileData * clone = nullptr;

    Luax::CatchException(L, [&]() { clone = data->Clone(); });
    Luax::PushType(L, clone);

    clone->Release();

    return 1;
}

int Wrap_FileData::GetFilename(lua_State * L)
{
    FileData * self = Wrap_FileData::CheckFileData(L, 1);

    lua_pushstring(L, self->GetFilename().c_str());

    return 1;
}

int Wrap_FileData::GetExtension(lua_State * L)
{
    FileData * self = Wrap_FileData::CheckFileData(L, 1);

    lua_pushstring(L, self->GetExtension().c_str());

    return 1;
}

FileData * Wrap_FileData::CheckFileData(lua_State * L, int index)
{
    return Luax::CheckType<FileData>(L, index);
}

int Wrap_FileData::Register(lua_State * L)
{
    luaL_Reg reg[] =
    {
        { "clone",        Clone        },
        { "getFilename",  GetFilename  },
        { "getExtension", GetExtension },
        { 0,              0            }
    };

    int ret = Luax::RegisterType(L, &FileData::type, reg, nullptr);
    // Data::RunDataWrapper(L, FileData::type);

    return ret;
}

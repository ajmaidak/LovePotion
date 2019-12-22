#include "common/runtime.h"
#include "modules/filesystem.h"

#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <libgen.h>

//Löve2D Functions

//love.filesystem.read
int Filesystem::Read(lua_State * L)
{
    std::string path = Redirect(luaL_checkstring(L, 1));
    size_t size = 0;
    char * buffer;

    FILE * fileHandle = fopen(path.c_str(), "rb");

    if (!fileHandle)
        return 0;

    fseek(fileHandle, 0, SEEK_END);
    size = ftell(fileHandle);
    rewind(fileHandle);

    buffer = (char *)malloc(size + 1);

    if (!buffer)
    {
        fclose(fileHandle);
        return 0;
    }

    fread(buffer, 1, size, fileHandle);

    fclose(fileHandle);

    buffer[size] = '\0';

    lua_pushstring(L, buffer);

    free(buffer);

    return 1;
}

//love.filesystem.write
int Filesystem::Write(lua_State * L)
{
    std::string path = GetSaveDirectory() + std::string(luaL_checkstring(L, 1));

    size_t length = 0;
    const char * data = luaL_checklstring(L, 2, &length);

    FILE * fileHandle = fopen(path.c_str(), "w");

    if (!fileHandle)
    {
        fclose(fileHandle);
        return 0;
    }

    fwrite(data, 1, length, fileHandle);

    fflush(fileHandle);

    fclose(fileHandle);

    return 0;
}

//love.filesystem.getInfo
int Filesystem::GetInfo(lua_State * L)
{
    std::string path = Redirect(luaL_checkstring(L, 1));
    std::string checkType;

    struct stat pathInfo;
    int success = stat(path.c_str(), &pathInfo);

    if (success != 0)
    {
        lua_pushnil(L);
        return 1;
    }

    if (lua_istable(L, 2))
        lua_pushvalue(L, 2);
    else
    {
        checkType = luaL_optstring(L, 2, "");
        lua_newtable(L);
    }

    std::string pathType = "other";
    if (S_ISREG(pathInfo.st_mode))
        pathType = "file";
    else if (S_ISDIR(pathInfo.st_mode))
        pathType = "directory";

    lua_pushstring(L, pathType.c_str());
    lua_setfield(L, -2, "type");

    if (checkType != "" && checkType != pathType)
    {
        lua_pop(L, 1);
        return 0;
    }

    double size = std::min((long long)pathInfo.st_size, 0x20000000000000LL);
    if (size >= 0)
        lua_pushnumber(L, size);
    else
        lua_pushnil(L);

    lua_setfield(L, -2, "size");

    double time = std::min((long long)pathInfo.st_mtime, 0x20000000000000LL);
    if (time >= 0)
        lua_pushnumber(L, time);
    else
        lua_pushnil(L);

    lua_setfield(L, -2, "modtime");

    return 1;
}

//love.filesystem.setIdentity
int Filesystem::SetIdentity(lua_State * L)
{
    m_identity = luaL_checkstring(L, 1);

    return 0;
}


//love.filesystem.getIdentity
int Filesystem::GetIdentity(lua_State * L)
{
    lua_pushstring(L, m_identity.c_str());

    return 1;
}

//love.filesystem.createDirectory
int Filesystem::CreateDirectory(lua_State * L)
{
    std::string path = GetSaveDirectory() + std::string(luaL_checkstring(L, 1));

    mkdir(path.c_str(), 0777);

    return 0;
}

//love.filesystem.getSaveDirectory
int Filesystem::GetSaveDirectory(lua_State * L)
{
    lua_pushstring(L, GetSaveDirectory().c_str());

    return 1;
}

//love.filesystem.getDirectoryItems
int Filesystem::GetDirectoryItems(lua_State * L)
{
    std::string path = Redirect(luaL_checkstring(L, 1));

    DIR * dp;

    dp = opendir(path.c_str());

    int tablepos = 0;

    if (dp != NULL)
    {
        lua_newtable(L);

        struct dirent * ep;

        while ((ep = readdir(dp)) != NULL)
        {
            if (ep->d_name[0] == '.')
                continue; //skip .

            tablepos++;

            lua_pushnumber(L, tablepos);
            lua_pushstring(L, ep->d_name);

            lua_settable(L, -3);
        }

        closedir(dp);

        return 1;
    }

    return 0;
}

//love.filesystem.load
int Filesystem::Load(lua_State * L)
{
    std::string path = Redirect(luaL_checkstring(L, 1));

    luaL_loadfile(L, path.c_str());

    return 1;
}

//love.filesystem.remove
int Filesystem::Remove(lua_State * L)
{
    std::string path = GetSaveDirectory() + std::string(luaL_checkstring(L, 1));

    remove(path.c_str());

    return 0;
}

//End Löve2D Functions

std::string Filesystem::GetSaveDirectory()
{
    return m_save_dir + "/";
}

std::string Filesystem::Redirect(const char * path)
{
    struct stat pathInfo;

    //Check save directory first
    std::string saveFile = GetSaveDirectory() + std::string(path);
    const char * filename = saveFile.c_str();

    int success = stat(filename, &pathInfo);

    if (success == 0)
        return saveFile;
    else
        return std::string(path);
}

//Register Functions
int Filesystem::Register(lua_State * L)
{
    luaL_reg reg[] =
    {
        { "createDirectory",        CreateDirectory   },
        { "getDirectoryItems",      GetDirectoryItems },
        { "getIdentity",            GetIdentity       },
        { "getInfo",                GetInfo           },
        { "getSaveDirectory",       GetSaveDirectory  },
        { "load",                   Load              },
        { "read",                   Read              },
        { "remove",                 Remove            },
        { "setIdentity",            SetIdentity       },
        { "write",                  Write             },
        { 0,                        0                 }
    };

    luaL_newlib(L, reg);

    return 1;
}

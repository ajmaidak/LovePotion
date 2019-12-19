#include "common/runtime.h"
#include "common/assets.h"

#include <unistd.h>
#include <dirent.h>

void Assets::Initialize(char * path)
{
    unsigned int gameAssets = Assets::GetLocation(path);

    switch(gameAssets)
    {
        case 0:
        {
            struct stat pathInfo;

            stat("game", &pathInfo);

            if (S_ISDIR(pathInfo.st_mode))
                location = "game";

            break;
        }
        case 1:
            romfsMountFromFsdev(path, 0, "romfs");

            break;
        default:
            break;
    }

    chdir(location.c_str());
}

unsigned int Assets::GetLocation(char * path)
{
    if (!path)
        return 0;

    const char * ext = strrchr(path, '.');

    if (strncmp(ext, ".lpx", 4) != 0)
    {
        Result rc = romfsInit();

        if (rc != 0)
            return 0;

        return 1;
    }

    return 2;
}

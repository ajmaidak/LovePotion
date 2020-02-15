#include "common/runtime.h"
#include "common/assets.h"

#include <unistd.h>
#include <dirent.h>

void Assets::Initialize(const std::string & path)
{
    size_t gameAssets = Assets::GetLocation(path);

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
        {
            romfsMountFromFsdev(path.c_str(), 0, "romfs");

            break;
        }
        default:
            break;
    }

    chdir(location.c_str());
}

size_t Assets::GetLocation(const std::string & path)
{
    if (path.empty())
        return 0;

    bool isROMFS = (path.substr(path.find_last_of(".")) == ".lpx");

    if (isROMFS)
    {
        Result rc = romfsInit();

        if (rc != 0)
            return 0;

        return 1;
    }

    return 2;
}

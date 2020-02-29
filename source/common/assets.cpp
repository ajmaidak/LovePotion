#include "common/runtime.h"
#include "common/assets.h"

#include <unistd.h>

void Assets::Initialize(const std::string & path)
{
    char current[PATH_MAX];
    writePath = getcwd(current, PATH_MAX);

    Location location = Assets::GetLocation(path);

    switch(location)
    {
        case LOCATION_SDMC:
            directory = "game";
            break;
        case LOCATION_EXTERNAL:
            romfsMountFromFsdev(path.c_str(), 0, "romfs");
            break;
        default:
        case LOCATION_ROMFS:
            break;
    }

    chdir(directory.c_str());
}

std::string Assets::GetWritePath()
{
    return writePath;
}

Location Assets::GetLocation(const std::string & path)
{
    if (path.empty())
        return LOCATION_SDMC;

    size_t extPosition = path.find_last_of(".");
    bool isROMFSGame = false;

    if (extPosition != std::string::npos)
        isROMFSGame = (path.substr(extPosition) == ".lpx");

    if (!isROMFSGame)
    {
        bool isDirectory = std::filesystem::is_directory(path);
        if (std::filesystem::exists("game") && isDirectory)
            return LOCATION_SDMC;
    }

    // couldn't grab game folder
    Result rc = romfsInit();

    // load our external ROMFS game
    if (rc == 0 && isROMFSGame)
        return LOCATION_EXTERNAL;

    // load no game / fused
    return LOCATION_ROMFS;
}

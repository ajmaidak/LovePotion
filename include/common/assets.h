/*
** common/assets.h
** @brief   : Loads game content
*/

#pragma once

enum Location
{
    SDMC = 0,
    ROMFS,
    EXTERNAL
};

class Assets
{
    public:
        Assets() = delete;
        static void Initialize(const std::string & path);

    private:
        static inline std::string directory = "romfs:";

        static Location GetLocation(const std::string & path);
};

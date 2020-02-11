/*
** common/assets.h
** @brief   : Loads game content
*/

class Assets
{
    public:
        Assets() = delete;
        static void Initialize(const std::string & path);

    private:
        static inline std::string location = "romfs:/";

        static size_t GetLocation(const std::string & path);
};

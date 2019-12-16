#pragma once

class Love
{
    public:
        Love() = delete;

        static int Initialize(lua_State * L);
        static void InitializeConstants(lua_State * L);

        static int Run(lua_State * L);

        static bool IsRunning();
        static int Quit(lua_State * L);

        // Various Utility Functions
        static int GetVersion(lua_State * L);
        static void InitConstants(lua_State * L);

        static void GetField(lua_State * L, const char * field);
        static int Preload(lua_State * L, lua_CFunction func, const char * name);

        static int GetRegistry(lua_State * L, int registry);
        static void RegObject(lua_State * L, int index, void * object);
        static void DeRegObject(lua_State * L, void * object);

        static void PushObject(lua_State * L, void * object);
        // End Various Utility Functions

        static void Register();
        static void Exit(lua_State * L);

    private:
        static inline bool quit = false;
        static inline std::array<love_modules, 15> modules = { nullptr };
};

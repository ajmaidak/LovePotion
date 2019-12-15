#pragma once

class Love
{
    public:
        Love() = delete;
        static int Initialize(lua_State * L);

        static int GetVersion(lua_State * L);
        static int InitConstants(lua_State * L);

        static void Register();
        static void Exit();

    private:
        static inline bool quit = false;

        static bool IsRunning();
};

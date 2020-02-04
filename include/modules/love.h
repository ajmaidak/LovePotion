#pragma once

#define TITLE_TAKEOVER_ERROR "Please run Löve Potion under Atmosphère title takeover."

class Love
{
    public:
        Love() = delete;

        static int Initialize(lua_State * L);
        static int Boot(lua_State * L);

        static int GetVersion(lua_State * L);

        static int Run(lua_State * L);

        static bool IsRunning();
        static int Quit(lua_State * L);

        // Various Utility Functions
        static void InitConstants(lua_State * L);

        static bool EnsureApplicationType(lua_State * L);

        static void GetField(lua_State * L, const char * field);
        static int Preload(lua_State * L, lua_CFunction func, const char * name);

        static int GetRegistry(lua_State * L, int registry);
        static void RegObject(lua_State * L, int index, void * object);
        static void DeRegObject(lua_State * L, void * object);

        static void PushObject(lua_State * L, void * object);
        // End Various Utility Functions

        static void Register();
        static void Exit(lua_State * L);

        typedef struct {
            const char * name;
            int (* reg)(lua_State * L);
            void (* close)(void);
        } Module;

    private:
        static inline bool m_quit = false;
        static inline std::array<Love::Module, 15> m_modules = { nullptr };
};

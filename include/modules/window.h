#pragma once

class Window
{
    public:
        Window() = delete;

        static int Register(lua_State * L);

    private:
        // Löve2D Functions

        static int SetMode(lua_State * L) { return 0; };

        static int GetDisplayCount(lua_State * L);

        static int GetFullscreenModes(lua_State * L);

        static int IsOpen(lua_State * L);

        // End Löve2D Functions
};

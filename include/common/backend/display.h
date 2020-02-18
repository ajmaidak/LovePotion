/*
** display.h
** Handles internal display information/rendering
*/

#pragma once

class Display
{
    public:
        Display() = delete;

        static void Initialize();

        static void Clear(Color * color);
        static int Draw(lua_State * L);
        static int Present(lua_State * L);

        static inline void SetBlendColor(Color * color) {
            m_blendColor = {color->r, color->g, color->b, color->a};
        }

        static int SetScreen(lua_State * L);

        static std::vector<std::pair<int, int>> GetWindowSizes();
        static unsigned int GetDisplayCount();

        static Renderer * GetRenderer();

        static bool IsOpen();

        static void Exit();

    private:
        static inline bool m_open = false;
        static inline std::vector<Renderer *> m_targets = { nullptr };
        static inline Frame * m_window = nullptr;

        static inline Color m_blendColor = { 1, 1, 1, 1 };
};

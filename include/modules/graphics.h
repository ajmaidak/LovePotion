/*
** modules/graphics.h
** @brief : handles graphical drawing
*/

class Graphics
{
    public:
        Graphics() = delete;

        static int Clear(lua_State * L);

        static int SetBackgroundColor(lua_State * L);
        static int GetBackgroundColor(lua_State * L);

        static int SetColor(lua_State * L);
        static int GetColor(lua_State * L);

        static int Register(lua_State * L);

    private:
        static inline float m_depth = 0.0f;

        static inline Color m_background = { 0, 0, 0, 1 };
        static inline Color m_foreground = { 1, 1, 1, 1 };

        static void AdjustColor(const Color & in, Color * out);
};

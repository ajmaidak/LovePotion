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

        static Color GetBackgroundColor();

        static int Register(lua_State * L);

    private:
        static inline float m_depth = 0.0f;
        static inline Color m_background = { 1, 1, 1, 1 };
};

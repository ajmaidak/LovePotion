/*
** modules/event.h
** @brief    : Handles events.. like quitting.. and other things
*/

#pragma once

class LoveEvent
{
    public:
        LoveEvent() = delete;

        static int Pump(lua_State * L);

        static bool IsTouchDown();

        static int Poll_I(lua_State * L);

        static int Poll(lua_State * L);

        static int Register(lua_State * L);

    private:
        static inline bool m_touchDown = false;
        static inline LOVE_Event m_event;

        //Löve2D Functions

        static int Quit(lua_State * L);

        static bool Poll(Message *& message);

        static inline std::queue<Message *> m_queue = {};

        //End Löve2D Functions
};

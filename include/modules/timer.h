/*
** modules/timer.h
** @brief : Used for time keeping
*/

#pragma once

class Timer
{
    public:
        Timer() = delete;

        static float GetDelta();

        static int Register(lua_State * L);

    private:
        static inline u32 m_lastTime = 0;
        static inline u32 m_currentTime = 0;
        static inline float m_deltatime = 0.0;

        static inline u32 m_lastCountTime = 0;
        static inline int m_totalFrames = 0;
        static inline int m_frames = 0;

        //Löve2D Functions

        static int GetFPS(lua_State * L);

        static int GetTime(lua_State * L);

        static int GetDelta(lua_State * L);

        static int Sleep(lua_State * L);

        static int Step(lua_State * L);

        //End Löve2D Functions
};

/*
** modules/timer.h
** @brief : Used for time keeping
*/

#pragma once

namespace love
{
    class Timer : public Module
    {
        public:
            Timer();
            virtual ~Timer() {}

            ModuleType GetModuleType() const { return M_TIMER; }

            const char * GetName() const override { return "love.timer"; }

            //Löve2D Functions

            float GetAverageDelta();

            float GetDelta();

            int GetFPS();

            static double GetTime();

            void Sleep(float ms);

            double Step();

            //End Löve2D Functions

        private:
            static inline double GetTimeOfDay() {
                timeval time;
                gettimeofday(&time, NULL);

                return (double) time.tv_sec + (double) time.tv_usec / 1000000.0;
            }

            float currentTime;
            float lastTime;
            float prevFPSUpdate;

            int fps;
            float averageDelta;

            float fpsUpdateFrequency;
            int frames;

            float dt;
    };
}

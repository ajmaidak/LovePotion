/*
** modules/event.h
** @brief    : Handles events.. like quitting.. and other things
*/

#pragma once

#include "modules/love.h"
#include "modules/joystick/joystick.h"

class LoveEvent : public Module
{
    public:
        virtual ModuleType GetModuleType() const { return M_EVENT; }

        const char * GetName() const override { return "love.event"; }

        ~LoveEvent() {}

        void Pump();

        void Push(Message * message);

        bool Poll(Message *& message);

        bool Quit();

    private:
        LOVE_Event loveEvent;
        std::queue<Message *> queue;
};

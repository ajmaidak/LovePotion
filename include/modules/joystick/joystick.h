#pragma once

#include "objects/gamepad/gamepad.h"
#include "objects/gamepad/wrap_gamepad.h"

class Joystick : public Module
{
    public:
        Joystick();
        virtual ~Joystick() {}

        virtual ModuleType GetModuleType() const { return M_JOYSTICK; }

        const char * GetName() const override { return "love.joystick"; }

        Gamepad * GetJoystickFromID(size_t index);

        size_t GetJoystickCount();

        void AddGamepad(Gamepad * gamepad);

    private:
        std::vector<Gamepad *> gamepads = {};
};

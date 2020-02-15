#pragma once

#include "objects/object.h"
#include "common/backend/input.h"

class Gamepad : public Object
{
    public:
        Gamepad(size_t id);

        static inline love::Type type = love::Type("Joystick", &Object::type);

        float GetAxis(size_t axis);

        size_t GetAxisCount();

        size_t GetButtonCount();

        float GetGamepadAxis(const std::string & axis);

        size_t GetID() { return (id + 1); };

        std::string GetName();

        float GetVibration();

        bool IsConnected();

        bool IsDown(size_t button);

        bool IsGamepad();

        bool IsGamepadDown(const std::string & button);

        bool IsVibrationSupported();

        bool SetVibration(float left, float right, float duration = 0.0f);

        virtual ~Gamepad() {}

    private:
        size_t id;
        StickPosition stick;
        float vibrations[2];
};

#pragma once

#include "objects/object.h"
#include "common/backend/input.h"

class Gamepad : public Object
{
    public:
        Gamepad(size_t id);

        static love::Type type;

        std::string GetName();

        bool IsGamepadDown(const std::string & button);
        bool IsDown(size_t button);

        size_t GetID() { return id; };

        virtual ~Gamepad() {}

    private:
        size_t id;
};

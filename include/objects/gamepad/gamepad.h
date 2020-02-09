#pragma once

#include "objects/object.h"

class Gamepad : public Object
{
    public:
        Gamepad(size_t id = 0);

        std::string GetName();

        bool IsDown(const std::string & button);
        size_t GetID() { return id; };

    private:
        size_t id;
};

#pragma once

class Gamepad : public Object
{
    public:
        Gamepad(size_t id);

        std::string GetName();

        bool IsDown(const std::string & button);
        size_t GetID() { return id; };

    private:
        size_t id;
};

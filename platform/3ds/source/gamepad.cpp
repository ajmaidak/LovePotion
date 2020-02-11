#include "common/runtime.h"
#include "objects/gamepad/gamepad.h"

love::Type Gamepad::type("Joystick", &Object::type);

Gamepad::Gamepad(size_t id)
{
    this->id = id;
}

bool Gamepad::IsGamepadDown(const std::string & button)
{
    auto buttons = Input::GetButtons();

    for (size_t index = 0; index < buttons.size(); index++)
    {
        if (BIT(index) & Input::GetKeyHeld())
        {
            if (Input::IsValid(buttons[index]) && button == buttons[index])
                return true;
        }
    }

    return false;
}

bool Gamepad::IsDown(size_t button)
{
    auto buttons = Input::GetButtons();

    if (BIT(button - 1) & Input::GetKeyHeld())
    {
        if (Input::IsValid(buttons[button - 1]))
            return true;
    }

    return false;
}

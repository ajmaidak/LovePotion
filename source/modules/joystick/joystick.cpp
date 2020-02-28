#include "common/runtime.h"
#include "modules/joystick/joystick.h"

using namespace love;

Joystick::Joystick()
{
    for (size_t index = 0; index < MAX_GAMEPADS; index++)
        this->AddGamepad(index);
}

size_t Joystick::GetJoystickCount()
{
    return this->gamepads.size();
}

Gamepad * Joystick::GetJoystickFromID(size_t index)
{
    if (index < 0 || index >= this->gamepads.size())
        return nullptr;

    return this->gamepads[index];
}

void Joystick::AddGamepad(size_t index)
{
    Gamepad * joystick = new Gamepad(index);
    this->gamepads.push_back(joystick);
}

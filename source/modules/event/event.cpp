#include "common/runtime.h"
#include "common/backend/input.h"

#include "modules/event/event.h"

void love::Event::Clear()
{
    while (!this->queue.empty())
    {
        this->queue.front()->Release();
        this->queue.pop();
    }
}

void love::Event::Pump()
{
    while (Input::PollEvent(&event))
    {
        Message * message = nullptr;

        love::Gamepad * gamepad = nullptr;
        love::Type * joystickType = &love::Gamepad::type;

        std::vector<love::Variant> vargs;
        vargs.reserve(4);

        auto joystickModule = love::Module::GetInstance<love::Joystick>(love::Module::M_JOYSTICK);

        switch (event.type)
        {
            case LOVE_GAMEPADUP:
            case LOVE_GAMEPADDOWN:
            {
                std::string field = (event.type == LOVE_GAMEPADDOWN) ?
                        "gamepadpressed" : "gamepadreleased";

                gamepad = joystickModule->GetJoystickFromID(event.button.which);

                if (!gamepad)
                    break;

                vargs.emplace_back(Proxy { joystickType, gamepad });
                vargs.emplace_back(event.button.name);

                message = new Message(field, vargs);

                break;
            }
            case LOVE_GAMEPADAXIS:
            {
                gamepad = joystickModule->GetJoystickFromID(event.axis.which);

                std::string field = "gamepadaxis";

                if (!gamepad)
                    break;

                vargs.emplace_back(Proxy { joystickType, gamepad });
                vargs.emplace_back(event.axis.axis);
                vargs.emplace_back((float)gamepad->GetGamepadAxis(event.axis.axis));

                message = new Message(field, vargs);

                break;
            }
            case LOVE_TOUCHPRESS:
            case LOVE_TOUCHRELEASE:
            {
                std::string field = (event.type == LOVE_TOUCHPRESS) ?
                         "touchpressed" : "touchreleased";

                vargs.emplace_back(&event.touch.id);
                vargs.emplace_back((float)event.touch.x);
                vargs.emplace_back((float)event.touch.y);
                vargs.emplace_back((float)1.0f);

                message = new Message(field, vargs);

                break;
            }
            default:
                break;
        }

        if (message)
            this->queue.push(message);
    }
}

bool love::Event::Poll(Message *& message)
{
    if (this->queue.empty())
        return false;

    message = this->queue.front();
    this->queue.pop();

    return true;
};

void love::Event::Push(Message * message)
{
    message->Retain();
    this->queue.push(message);
}

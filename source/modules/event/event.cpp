#include "common/runtime.h"
#include "common/backend/input.h"

#include "modules/event/event.h"

void LoveEvent::Pump()
{
    while (Input::PollEvent(&loveEvent))
    {
        Message * message = nullptr;

        Gamepad * gamepad = nullptr;
        love::Type * joystickType = &Gamepad::type;

        std::vector<Variant> vargs;
        vargs.reserve(7);

        auto joystickModule = Module::GetInstance<Joystick>(Module::M_JOYSTICK);

        switch (loveEvent.type)
        {

            case LOVE_GAMEPADUP:
            case LOVE_GAMEPADDOWN:
            {
                std::string field = (loveEvent.type == LOVE_GAMEPADDOWN) ?
                        "gamepadpressed" : "gamepadreleased";

                gamepad = joystickModule->GetJoystickFromID(loveEvent.button.which);

                if (!gamepad)
                    break;

                vargs.emplace_back(Proxy { joystickType, gamepad });
                vargs.emplace_back(loveEvent.button.name);

                message = new Message(field, vargs);

                break;
            }
            case LOVE_GAMEPADAXIS:
            {
                gamepad = joystickModule->GetJoystickFromID(loveEvent.axis.which);

                std::string field = "gamepadaxis";

                if (!gamepad)
                    break;

                vargs.emplace_back(Proxy { joystickType, gamepad });

                std::string axis = loveEvent.axis.axis;
                vargs.emplace_back(axis);

                float value = gamepad->GetGamepadAxis(axis);
                vargs.emplace_back(value);

                message = new Message(field, vargs);

                break;
            }
            case LOVE_TOUCHPRESS:
            case LOVE_TOUCHRELEASE:
            {
                std::string field = (loveEvent.type == LOVE_TOUCHPRESS) ?
                         "touchpressed" : "touchreleased";

                vargs.emplace_back(&loveEvent.touch.id);
                vargs.emplace_back((float)loveEvent.touch.x);
                vargs.emplace_back((float)loveEvent.touch.y);
                vargs.emplace_back(0.0f);
                vargs.emplace_back(0.0f);
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

bool LoveEvent::Poll(Message *& message)
{
    if (this->queue.empty())
        return false;

    message = this->queue.front();
    this->queue.pop();

    return true;
};

void LoveEvent::Push(Message * message)
{
    message->Retain();
    this->queue.push(message);
}

//End Löve2D Functions

// bool LoveEvent::IsTouchDown()
// {
//     return m_touchDown;
// }

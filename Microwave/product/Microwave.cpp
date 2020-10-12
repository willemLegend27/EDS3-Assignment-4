#include "Microwave.h"

#include <iostream>

Microwave::Microwave(ILight& light, IMotor& motor, ISystem& system, IUserInterface& ui)
    : currentState(STATE_IDLE)
    , light(light)
    , motor(motor)
    , system(system)
    , ui(ui)
{
}

States Microwave::HandleIdleState(Events ev)
{
    States result = STATE_IDLE;

    switch (ev)
    {
    case EV_START:
        result = STATE_HEATING;
        break;

    default:
        // ignored event, nothing to do here
        break;
    }

    return result;
}

void Microwave::HandleEvent(Events ev)
{
    switch (currentState)
    {
    case STATE_IDLE:
        currentState = HandleIdleState(ev);
        break;

    default:
        std::cerr << "ERROR: illegal/unhandled state with number: " << currentState;
        break;
    };
}

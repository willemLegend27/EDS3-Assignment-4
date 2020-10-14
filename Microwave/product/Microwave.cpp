#include "Microwave.h"

#include <iostream>

Microwave::Microwave(ILight& light, IMotor& motor, ISystem& system, IUserInterface& ui)
    : currentState(STATE_IDLE)
    , light(light)
    , motor(motor)
    , system(system)
    , ui(ui)
{
    motor.SetPower(0);
}

States Microwave::HandleIdleState(Events ev)
{
    States result = STATE_IDLE;

    switch (ev)
    {
    case EV_START:
        //IdleExitAction();
        result = STATE_HEATING;
        motor.SetPower(ui.GetRequestedPower());
        //HeatingEntryAction();
        break;
    // case :
    //     break;
    default:
        // ignored event, nothing to do here
        break;
    }

    return result;
}

States Microwave::HandleHeatingPausedState(Events ev)
{
    States result = STATE_HEATING;
    switch(ev){
        case EV_DOOR_CLOSED:
            light.Off();
            result = STATE_HEATING;
            break;
        case EV_DOOR_OPENED:
            light.On();
            result = STATE_HEATING_PAUSED;
            break;
        default:
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
    case STATE_HEATING_PAUSED:
        currentState = HandleHeatingPausedState(ev);
        break;
    default:
        std::cerr << "ERROR: illegal/unhandled state with number: " << currentState;
        break;
    };
}

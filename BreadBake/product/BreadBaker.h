#ifndef BREADBAKER_H
#define BREADBAKER_H

#include "Events.h"
#include "IDisplay.h"
#include "IEventGenerator.h"
#include "IExtraIngredientsTray.h"
#include "IKneadMotor.h"
#include "IOven.h"
#include "IStartButtonLed.h"
#include "ITimer.h"
#include "IYeastTray.h"
#include "Log.h"
#include "States.h"

class BreadBaker
{
public:
    BreadBaker(IEventGenerator& eventGenerator);

    BreadBaker(const BreadBaker& other) = delete;
    BreadBaker& operator=(const BreadBaker&) = delete;

    void Run(volatile bool* quit);

    // For testing purposes
    // You'll have to decide yourself if you'd rather:
    // - have these methods private (better encapsulation)
    // - be able to test these methods
    // You cannot have both at the same time (without dirty tricks)
    void HandleEvent(Events ev);

private:
    IEventGenerator& eventGenerator;
};


#endif

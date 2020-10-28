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
#include "Program.h"
#include "Producing_Substates.h"
#include "Kneading_Substates.h"

class BreadBaker
{
private:
    IEventGenerator &eventGenerator;
    ITimer &timer;
    IOven &oven;
    IStartButtonLed &startButton;
    IDisplay &display;
    IExtraIngredientsTray &extras;
    IYeastTray &yeast;
    IKneadMotor &kneadMotor;

    States currentState;
    Producing_Substates producingState;
    Kneading_Substates kneadingState;
    Kneading_Substates prevKneadingState;
    bool enterState = true;
    bool enterProducingSubState = true;
    bool enterKneadingSubState = true;
    int totalTimeInMs = 0;
    Program program;
public:
    BreadBaker(IEventGenerator &eventGenerator, ITimer &timer, IOven &oven, IStartButtonLed &startButton, IDisplay &display, IExtraIngredientsTray &extras, IYeastTray &yeast, IKneadMotor &kneadMotor);

    BreadBaker(const BreadBaker &other) = delete;
    BreadBaker &operator=(const BreadBaker &) = delete;

    void Run(volatile bool *quit);

private:
    // For testing purposes
    // You'll have to decide yourself if you'd rather:
    // - have these methods private (better encapsulation)
    // - be able to test these methods
    // You cannot have both at the same time (without dirty tricks)
    ///[I chose to have this method private]
    void HandleEvent(Events ev);
    void HandleState(States state);
    void HandleProducingSubState(Producing_Substates producingState);
    void HandleKneadingSubState(Kneading_Substates kneadingState);
};

#endif

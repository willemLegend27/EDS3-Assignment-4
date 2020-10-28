#include "BreadBaker.h"
#include <thread>

BreadBaker::BreadBaker(IEventGenerator &eventGenerator, ITimer &timer, IOven &oven, IStartButtonLed &startButton, IDisplay &display, IExtraIngredientsTray &extras, IYeastTray &yeast, IKneadMotor &kneadMotor)
    : eventGenerator(eventGenerator), timer(timer), oven(oven), startButton(startButton), display(display), extras(extras), yeast(yeast), kneadMotor(kneadMotor)
{
    currentState = STANDBY;
}

void BreadBaker::Run(volatile bool *quit)
{
    program.waiting = 60;
    program.kneading = 20;
    program.rising = 160;
    program.baking = 50;
    program.addYeast = true;
    program.addExtras = true;
    while (!*quit)
    {
        Events ev = eventGenerator.GetEvent();
        HandleEvent(ev);
        HandleState(currentState);
        HandleProducingSubState(producingState);
        HandleKneadingSubState(kneadingState);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void BreadBaker::HandleState(States state)
{
    switch (state)
    {
    case STANDBY:
        if (enterState == true)
        {
            display.DisplayOff();
            startButton.LedOff();
            enterState = false;
        }
        break;
    case SETUP:
        if (enterState == true)
        {
            display.SetMenuNumber(1);
            enterState = false;
        }
        break;
    case BLINKING_START:
        if (enterState == true)
        {
            startButton.LedOff();
            totalTimeInMs = 500;
            timer.Set(totalTimeInMs);
            enterState = false;
        }
        break;
    case PRODUCING:
        if (enterState == true)
        {
            producingState = RESTING;
            enterState = false;
        }
        break;
    }
}

void BreadBaker::HandleProducingSubState(Producing_Substates producingState)
{
    switch (producingState)
    {
    case RESTING:
        if (enterProducingSubState == true)
        {
            display.SetCurrentTask(Waiting);
            timer.Set(program.waiting);
            enterProducingSubState = false;
        }
        break;
    case KNEADING:
        if (enterProducingSubState == true)
        {
            display.SetCurrentTask(Kneading);
            timer.Set(program.kneading);
            extras.Drop(15);
            yeast.Drop(program.kneading / 2);
            kneadingState = KNEADING_LEFT;
            enterKneadingSubState = true;
            enterProducingSubState = false;
        }
        break;
    case RISING:
        if (enterProducingSubState == true)
        {
            display.SetCurrentTask(Rising);
            oven.StartRise(program.rising);
            enterProducingSubState = false;
        }
        break;
    case BAKING:
        if (enterProducingSubState == true)
        {
            display.SetCurrentTask(Baking);
            oven.StartRise(program.baking);
            enterProducingSubState = false;
        }
        break;
    case DONE:
        if (enterProducingSubState == true)
        {
            display.SetCurrentTask(Done);
            timer.Set(5);
            enterProducingSubState = false;
        }
        break;
    default:
        break;
    }
}
void BreadBaker::HandleKneadingSubState(Kneading_Substates kneadingState)
{
    switch (kneadingState)
    {
    case KNEADING_LEFT:
        if (enterKneadingSubState == true)
        {
            kneadMotor.TurnLeft();
            timer.Set(1);
            enterKneadingSubState = false;
        }
        break;
    case STOP_KNEADING:
        if (enterKneadingSubState == true)
        {
            kneadMotor.Stop();
            if (prevKneadingState == KNEADING_RIGHT)
            {
                kneadingState = KNEADING_LEFT;
                enterKneadingSubState = true;
            }
            else if (prevKneadingState == KNEADING_LEFT)
            {
                kneadingState = KNEADING_RIGHT;
                enterKneadingSubState = true;
            }
            enterKneadingSubState = false;
        }
        break;
    case KNEADING_RIGHT:
        if (enterKneadingSubState == true)
        {
            kneadMotor.TurnRight();
            timer.Set(1);
            enterKneadingSubState = false;
        }
        break;
    default:
        break;
    }
}

// parameter name in comment to prevent compiler warning as it is unused for now
void BreadBaker::HandleEvent(Events ev)
{
    switch (ev)
    {
    case NoEventOccurred:

        break;
    case MenuBtnLongPressed:
        if (currentState == PRODUCING)
        {
            currentState = STANDBY;
            extras.Cancel();
            timer.Cancel();
            yeast.Cancel();
            oven.Cancel();
        }
        break;
    case MenuBtnPressed:
        if (currentState == STANDBY)
        {
            currentState = SETUP;
            totalTimeInMs = 60000 * 5;
            timer.Set(totalTimeInMs);
        }
        else if (currentState == SETUP)
        {
            //program++
        }
        break;
    case StartBtnPressed:
        if (currentState == SETUP)
        {
            if (oven.GetTemperature() <= 50)
            {
                startButton.LedOn();
                currentState = PRODUCING;
                enterState = true;
            }
            else
            {
                currentState = BLINKING_START;
                enterState = true;
            }
        }
        break;
    case TimerDownBtnPressed:
        if (currentState == SETUP)
        {
            if (/*programTime >*/ totalTimeInMs)
            {
                totalTimeInMs = 60000 * 10;
                timer.Set(/*programTime - */ totalTimeInMs);
            }
        }
        break;
    case TimerUpBtnPressed:
        if (currentState == SETUP)
        {
            if (totalTimeInMs < (60000 * 60 * 12))
            {
                totalTimeInMs = 60000 * 10;
                timer.Set(/*programTime + */ totalTimeInMs);
            }
        }
        break;
    case TimerTimeout:
        if (currentState == SETUP)
        {
            currentState = STANDBY;
            enterState = true;
        }
        else if (currentState == BLINKING_START)
        {
            /*guard count>=10*/
            currentState = SETUP;
        }
        else if (currentState == PRODUCING)
        {
            display.SetTime((totalTimeInMs * 60000 * 60), (totalTimeInMs * 60000 * 60) / 60);
        }
        if (producingState == RESTING)
        {
            producingState = KNEADING;
            enterProducingSubState = true;
        }
        else if (producingState == DONE)
        {
            break;
        }
        if (kneadingState == KNEADING_LEFT)
        {
            prevKneadingState = KNEADING_LEFT;
            kneadingState = STOP_KNEADING;
            enterKneadingSubState = true;
        }
        else if (kneadingState == KNEADING_RIGHT)
        {
            prevKneadingState = KNEADING_RIGHT;
            kneadingState = STOP_KNEADING;
            enterKneadingSubState = true;
        }
        else if (kneadingState == STOP_KNEADING)
        {
            producingState = RISING;
            enterProducingSubState = true;
            enterKneadingSubState = false;
        }
        break;
    case OvenDone:
        if (currentState == PRODUCING)
        {
            currentState = STANDBY;
            enterState = true;
        }
        if (producingState == RISING)
        {
            producingState = BAKING;
            enterProducingSubState = true;
        }
        break;
    default:

        break;
    }
}

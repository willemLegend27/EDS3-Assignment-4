#include "BreadBaker.h"
#include "Program.h"

#include <thread>

BreadBaker::BreadBaker(IEventGenerator &eventGenerator, ITimer &timer, IOven &oven, IStartButtonLed &startButton, IDisplay &display, IExtraIngredientsTray &extras, IYeastTray &yeast, IKneadMotor &kneadMotor)
    : eventGenerator(eventGenerator), timer(timer), oven(oven), startButton(startButton), display(display), extras(extras), yeast(yeast), kneadMotor(kneadMotor)
{
    currentState = Standby;
}

void BreadBaker::Run(volatile bool *quit)
{
    while (!*quit)
    {
        Events ev = eventGenerator.GetEvent();
        HandleEvent(ev);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

// parameter name in comment to prevent compiler warning as it is unused for now
void BreadBaker::HandleEvent(Events ev)
{

    switch (currentState)
    {
    case Standby:
        if (enterState == true)
        {
            display.DisplayOff();
            startButton.LedOff();
            enterState = false;
        }
        if (ev == MenuBtnPressed)
        {
            currentState = Setup;
            enterState = true;
            totalTimeInMs = 60000 * 5;
            timer.Set(totalTimeInMs);
        }
        break;
    case Setup:
        if (enterState == true)
        {
            display.SetMenu(1);
            enterState = false;
        }
        if (ev == MenuBtnPressed)
        {
            //program++
        }
        else if (ev == TimerUpBtnPressed)
        {
            if (totalTimeInMs < (60000 * 60 * 12))
            {
                totalTimeInMs = 60000 * 10;
                timer.Set(/*programTime + */ totalTimeInMs);
            }
        }
        else if (ev == TimerDownBtnPressed)
        {
            if (/*programTime >*/ totalTimeInMs)
            {
                totalTimeInMs = 60000 * 10;
                timer.Set(/*programTime - */ totalTimeInMs);
            }
        }
        else if (ev == StartBtnPressed)
        {
            if (oven.GetTemperature() <= 50)
            {
                startButton.LedOn();
                currentState = Producing;
                enterState = true;
            }
            else
            {
                currentState = Blinking_Start;
                enterState = true;
            }
        }
        else if (ev == TimerTimeout)
        {
            currentState = Standby;
            enterState = true;
        }
        break;
    case Producing:
        if (enterState == true)
        {

            enterState = false;
        }
        if (ev == MenuBtnLongPressed)
        {
            currentState = Standby;
        }
        break;
    case Blinking_Start:
        if (enterState == true)
        {
            startButton.LedOff();
            totalTimeInMs = 500;
            timer.Set(totalTimeInMs);
            enterState = false;
        }
        if (ev == TimerTimeout)
        {
            /*guard count>=10*/
            currentState = Setup;
        }
    default:

        break;
    }
}

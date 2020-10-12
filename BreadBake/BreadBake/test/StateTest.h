#ifndef TESTSTATE_H
#define TESTSTATE_H

#include "BreadBaker.h"
#include "BrokenLog.h"
#include "MDisplay.h"
#include "MEventGenerator.h"
#include "MExtraIngredientsTray.h"
#include "MKneadMotor.h"
#include "MOven.h"
#include "MStartButtonLed.h"
#include "MTimer.h"
#include "MYeastTray.h"

class StateTest: public ::testing::Test
{
protected:
    StateTest()
    {
        baker = new BreadBaker(event);
    }

    virtual ~StateTest()
    {
        delete baker;
        baker = nullptr;
    }

    MDisplay display;
    MEventGenerator event;
    MExtraIngredientsTray extras;
    MKneadMotor motor;
    MOven oven;
    MStartButtonLed startButton;
    MTimer timer;
    MYeastTray yeast;
    BrokenLog log;
    BreadBaker* baker;
};

#endif

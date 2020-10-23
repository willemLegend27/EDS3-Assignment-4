#include "Microwave.h"

#include "MLight.h"
#include "MMotor.h"
#include "MSystem.h"
#include "MUserInterface.h"

using ::testing::Return;
using ::testing::_;

class TestHeatingPausedState : public ::testing::Test
{
protected:
    TestHeatingPausedState() 
    {
        EXPECT_CALL(motor, SetPower(0));
        microwave = new Microwave(light, motor, system, ui);
    }

    virtual ~TestHeatingPausedState() {}

    MLight light;
    MMotor motor;
    MSystem system;
    MUserInterface ui;
    Microwave* microwave;
};

TEST_F(TestHeatingPausedState, test_door_opened_event)
{
    EXPECT_CALL(light, On());
    EXPECT_EQ(STATE_HEATING_PAUSED, microwave->HandleHeatingPausedState(EV_DOOR_OPENED));
}

TEST_F(TestHeatingPausedState, test_door_closed_event)
{
    EXPECT_CALL(light, Off());
    EXPECT_EQ(STATE_HEATING, microwave->HandleHeatingPausedState(EV_DOOR_CLOSED));
}

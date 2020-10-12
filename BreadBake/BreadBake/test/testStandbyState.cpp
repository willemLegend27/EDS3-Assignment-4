#include "StateTest.h"

using ::testing::Return;
using ::testing::_;

TEST_F(StateTest, bogustest)
{
    EXPECT_CALL(display, SetCurrentTask(_)).Times(0);
    EXPECT_CALL(display, SetMenu(_)).Times(0);
    EXPECT_CALL(display, SetTime(_, _)).Times(0);
    EXPECT_CALL(display, DisplayOff()).Times(0);

    EXPECT_CALL(event, GetEvent()).Times(0);

    EXPECT_CALL(extras, Drop(_)).Times(0);
    EXPECT_CALL(extras, Cancel()).Times(0);

    EXPECT_CALL(motor, TurnLeft()).Times(0);
    EXPECT_CALL(motor, TurnRight()).Times(0);
    EXPECT_CALL(motor, Stop()).Times(0);

    EXPECT_CALL(oven, StartRise(_)).Times(0);
    EXPECT_CALL(oven, StartBake(_)).Times(0);
    EXPECT_CALL(oven, IsOn()).Times(0);
    EXPECT_CALL(oven, GetTemperature()).Times(0);
    EXPECT_CALL(oven, Cancel()).Times(0);

    EXPECT_CALL(startButton, LedOn()).Times(0);
    EXPECT_CALL(startButton, LedOff()).Times(0);

    EXPECT_CALL(timer, Set(_)).Times(0);
    EXPECT_CALL(timer, Cancel()).Times(0);

    EXPECT_CALL(yeast, Drop(_)).Times(0);
    EXPECT_CALL(yeast, Cancel()).Times(0);

    EXPECT_EQ(0, 0);
}

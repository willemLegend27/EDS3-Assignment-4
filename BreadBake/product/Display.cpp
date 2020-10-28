#include "Display.h"

static const char *TaskText[] = {"No task", "Waiting", "Kneading",
                                 "Rising", "Baking", "Done"};
static const char *MenuText[] = {"Bread", "Bread +", "Bread Quick", "Dough",
                                 "Bake Only"};

Display::Display(Log &log)
    : log(log)
{
}

void Display::SetCurrentTask(Tasks task)
{
    log.Debug(">> %s: %s", __FUNCTION__, TaskText[task]);
}

void Display::SetMenuNumber(int number)
{
    log.Debug(">> %s: %s", __FUNCTION__, MenuText[number]);
}

void Display::SetTime(int hour, int min)
{
    log.Debug(">> %s: %d:%d", __FUNCTION__, hour, min);
}

void Display::DisplayOff()
{
    log.Debug(">> %s", __FUNCTION__);
}

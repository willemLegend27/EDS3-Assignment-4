#include "EventGenerator.h"

static const char* EventStrings[] = {
    "NoEventOccurred",
    "MenuBtnPressed",
    "MenuBtnLongPressed",
    "TimerUpBtnPressed",
    "TimerDownBtnPressed",
    "StartBtnPressed",
    "OvenDone",
    "TimerTimeout"
};

EventGenerator::EventGenerator(IOven& oven, Log& log)
    : oven(oven)
    , prevOvenOn(false)
    , log(log)
{
}

Events EventGenerator::GetEvent()
{
    Events result = NoEventOccurred;

    HandlePollEvents();

    if (events.size() > 0)
    {
        result = events[0];
        events.erase(events.begin());
        log.Debug("== GetEvent returns: %s", EventStrings[result]);
    }

    return result;
}

void EventGenerator::TimerTimeout()
{
    PushEvent(Events::TimerTimeout);
}
void EventGenerator::MenuPressed()
{
    PushEvent(MenuBtnPressed);
}
void EventGenerator::MenuLongPressed()
{
    PushEvent(MenuBtnLongPressed);
}
void EventGenerator::TimerUpPressed()
{
    PushEvent(TimerUpBtnPressed);
}
void EventGenerator::TimerDownPressed()
{
    PushEvent(TimerDownBtnPressed);
}
void EventGenerator::StartPressed()
{
    PushEvent(StartBtnPressed);
}


void EventGenerator::HandlePollEvents()
{
    if (oven.IsOn())
    {
        prevOvenOn = true;
    }
    else
    {
        if (prevOvenOn)
        {
            prevOvenOn = false;
            PushEvent(OvenDone);
        }
    }
}

void EventGenerator::PushEvent(Events event)
{
    events.push_back(event);
    log.Debug("%s event occurred", EventStrings[event]);
}

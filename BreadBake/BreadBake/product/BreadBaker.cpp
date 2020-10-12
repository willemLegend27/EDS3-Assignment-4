#include "BreadBaker.h"
#include "Program.h"

#include <thread>

BreadBaker::BreadBaker(IEventGenerator& eventGenerator)
    : eventGenerator(eventGenerator)
{
}

void BreadBaker::Run(volatile bool* quit)
{
    while (!*quit)
    {
        Events ev = eventGenerator.GetEvent();
        HandleEvent(ev);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

// parameter name in comment to prevent compiler warning as it is unused for now
void BreadBaker::HandleEvent(Events /* ev */)
{
}

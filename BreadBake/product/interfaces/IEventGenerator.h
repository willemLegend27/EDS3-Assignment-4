#ifndef IEVENTGENERATOR_H
#define IEVENTGENERATOR_H

#include "Events.h"

class IEventGenerator
{
public:
    virtual ~IEventGenerator() {};

    virtual Events GetEvent() = 0;
};

#endif

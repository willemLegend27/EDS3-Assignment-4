#ifndef TIMER_H
#define TIMER_H

#include "ITimer.h"
#include "ITimerTimeout.h"
#include "Log.h"

#include <thread>

class Timer: public ITimer
{
public:
    Timer(ITimerTimeout& timerTimeout, Log& log);

    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;

    // ITimer
    void Set(uint64_t time);
    void Cancel();
    

private:
    ITimerTimeout& timerTimeout;
    Log& log;

    uint64_t GetSimulatedTime(uint64_t time);
    void CountDownTimer(uint64_t time);
};

#endif

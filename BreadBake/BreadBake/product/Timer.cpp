#include "Timer.h"

// To prevent endless waiting during testing, your timer can make use of the
// GetSimulatedTime method, which will divide waiting time by factor
// TimeDivider and will limit the maximum waiting time to MaxTimeInMiliseconds.
// To get reasonably normal timing, set TimeDivider to 1 and MaxTimeInMiliseconds
// to std::numeric_limits<uint64_t>::max() (or another really big number).
const uint64_t TimeDivider = 100;
const uint64_t MaxTimeInMiliseconds = 4000;
#define MS / 60000

Timer::Timer(ITimerTimeout& timerTimeout, Log& log)
    : timerTimeout(timerTimeout)
    , log(log)
{
}

void Timer::Set(uint64_t time)
{
    uint64_t nrTicks = GetSimulatedTime(time);
    log.Debug("timer set to: %lu ms (%lu min  ==> simulated time: %lu ms)", time, time MS,
              nrTicks);
}

void Timer::Cancel()
{
    log.Trace(">> %s", __FUNCTION__);
}


uint64_t Timer::GetSimulatedTime(uint64_t time)
{
    uint64_t simulatedTime = time / TimeDivider;
    if (simulatedTime > MaxTimeInMiliseconds)
    {
        simulatedTime = MaxTimeInMiliseconds;
    }
    return simulatedTime;
}
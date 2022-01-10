#include "Switcher.h"

#include "Arduino.h"


Switcher::Switcher(int pin, int debounceTimeMs)
: mPin(pin)
, mDebounceTimeUs(debounceTimeMs * 1000)
, mLastCheckTime(micros())
{
    pinMode(mPin, INPUT_PULLUP);
}

bool Switcher::checkChanges(long currTime)
{
    const auto actual = digitalRead(mPin) ? On : Off;

    if (actual != mState)
    {
        const auto elapsed = currTime - mLastCheckTime;
        if (elapsed >= mDebounceTimeUs)
        {
            mState = actual;
            mLastCheckTime = currTime;
            return true;
        }
    }
    else 
    {
        mLastCheckTime = currTime;
    }

    return false;
}

Switcher::State Switcher::state() const
{
    return mState;
}

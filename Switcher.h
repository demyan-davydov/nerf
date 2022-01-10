#pragma once

//
// On/Off switch (button) + debounce
//

class Switcher
{
public:
    enum State
    {
        Undefined = -1,
        Off = 0,
        On = 1
    };

    Switcher(int pin, int debounceTimeMs = 50);

    //! @returns true if state was changed since last checkChanges() call
    bool checkChanges(long currTime);

    //! @returns current switcher state
    State state() const;

private:
    int mPin = 0;
    int mDebounceTimeUs = 0;
    
    State mState = Undefined; // On | Off

    long mLastCheckTime;
};
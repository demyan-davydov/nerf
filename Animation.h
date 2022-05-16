#pragma once

#include "types.h"

class Animation
{
public:
    virtual ~Animation() = default;

    virtual void perform(long currTime, long totalTime, int repeatCount) const = 0;
};

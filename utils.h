#pragma once

#include "Arduino.h" // map()

//! @returns a * b / c
inline long mulDiv(long a, long b, long c)
{
    return map(b, 0, c, 0, a);
}

//! Translates the 'x' from range [0..inMax] to range [0..outMax]
inline long map(long x, long inMax, long outMax)
{
    return map(x, 0, inMax, 0, outMax);
}

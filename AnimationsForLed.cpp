#pragma once

#include "AnimationsForLed.h"

#include "utils.h"



void BecomeFullLedAnimation::perform(long currTime, long totalTime, int repeatCount) const
{
    const auto y = map(currTime, totalTime, 255); 

    mLed.color(0, y, 0);
}

void BecomeEmptyLedAnimation::perform(long currTime, long totalTime, int repeatCount) const
{
    const auto y = map(currTime, totalTime, 255); 

    mLed.color(y, 0, 0);
}

void FadeLedAnimation::perform(long currTime, long totalTime, int repeatCount) const
{
    const auto r = map(currTime, 0, totalTime, mFrom.r, mTo.r);
    const auto g = map(currTime, 0, totalTime, mFrom.g, mTo.g);
    const auto b = map(currTime, 0, totalTime, mFrom.b, mTo.b);

    mLed.color(r, g, b);
}

void FadeInLedAnimation::perform(long currTime, long totalTime, int repeatCount) const
{
    const auto r = map(currTime, totalTime, mColor.r);
    const auto g = map(currTime, totalTime, mColor.g);
    const auto b = map(currTime, totalTime, mColor.b);

    mLed.color(r, g, b);
}

void FadeOutLedAnimation::perform(long currTime, long totalTime, int repeatCount) const
{
    const auto r = map(currTime, 0, totalTime, mColor.r, 0);
    const auto g = map(currTime, 0, totalTime, mColor.g, 0);
    const auto b = map(currTime, 0, totalTime, mColor.b, 0);

    mLed.color(r, g, b);
}

void PowerOnLedAnimation::perform(long currTime, long totalTime, int repeatCount) const
{
    const auto h = map(currTime, totalTime, 255) + mHueOffset;

    mLed.color(ColorRgb::fromIntHsv((ubyte)h, mSaturation, mValue));
}

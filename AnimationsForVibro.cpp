#pragma once

#include "AnimationsForVibro.h"

#include "utils.h"


void BecomeFullVibroAnimation::perform(long currTime, long totalTime, int repeatCount) const
{
    if (currTime == totalTime)
    {
        mVibro.speed(0);
        return;
    }

    enum { kSteps = 3 };
    const int fromSteps[kSteps] = {0, 50, 100};
    const int toSteps[kSteps] = {50, 100, 200};
    const int step = repeatCount > kSteps - 1 ? kSteps - 1 : repeatCount;
    const int from = fromSteps[step];
    const int to = toSteps[step];

    const int speed = currTime < totalTime/2 ? map(currTime, 0, totalTime/2, from, to) : to;

    mVibro.speed(speed);
}

void BecomeEmptyVibroAnimation::perform(long currTime, long totalTime, int repeatCount) const
{
    if (currTime == totalTime)
    {
        mVibro.speed(0);
        return;
    }

    enum { kSteps = 3 };
    const int fromSteps[kSteps] = {200, 100, 50};
    const int toSteps[kSteps] = {100, 50, 0};
    const int step = repeatCount > kSteps - 1 ? kSteps - 1 : repeatCount;
    const int from = fromSteps[step];
    const int to = toSteps[step];

    const int speed = currTime < totalTime/2 ? map(currTime, 0, totalTime/2, from, to) : to;

    mVibro.speed(speed);
}


VibroAnimation::~VibroAnimation()
{
    mVibro.speed(0);
}

void VibroAnimation::perform(long currTime, long totalTime, int repeatCount) const
{
    auto speed = map(currTime, 0, totalTime, mFrom, mTo);
    mVibro.speed(speed);
}

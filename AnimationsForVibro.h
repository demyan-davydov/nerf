#pragma once

#include "Animation.h"

#include "Vibro.h"

#include "types.h"

class BecomeFullVibroAnimation : public Animation
{
    Vibro& mVibro;

public:
    BecomeFullVibroAnimation(Vibro& vibro) : mVibro(vibro) {}

    void perform(long currTime, long totalTime, int repeatCount) const override;
};

class BecomeEmptyVibroAnimation : public Animation
{
    Vibro& mVibro;

public:
    BecomeEmptyVibroAnimation(Vibro& vibro) : mVibro(vibro) {}

    void perform(long currTime, long totalTime, int repeatCount) const override;
};

class VibroAnimation : public Animation
{
    Vibro& mVibro;

    ubyte mFrom = 0;
    ubyte mTo = 0;

public:
    VibroAnimation(Vibro& vibro, ubyte from, ubyte to) : mVibro(vibro), mFrom(from), mTo(to) {}
    VibroAnimation(Vibro& vibro, ubyte speed) : mVibro(vibro), mFrom(speed), mTo(speed) {}
    ~VibroAnimation();

    void perform(long currTime, long totalTime, int repeatCount) const override;
};
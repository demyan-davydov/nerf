#pragma once

#include "Animation.h"

#include "Vibro.h"


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

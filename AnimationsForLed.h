#pragma once

#include "Animation.h"

#include "RgbLed.h"

#include "types.h"


class BecomeFullLedAnimation : public Animation
{
    RgbLed& mLed;

public:
    BecomeFullLedAnimation(RgbLed& led) : mLed(led) {}

    void perform(long currTime, long totalTime, int repeatCount) const override;
};

class BecomeEmptyLedAnimation : public Animation
{
    RgbLed& mLed;

public:
    BecomeEmptyLedAnimation(RgbLed& led) : mLed(led) {}

    void perform(long currTime, long totalTime, int repeatCount) const override;
};

class FadeLedAnimation : public Animation
{
    RgbLed& mLed;
    ColorRgb mFrom;
    ColorRgb mTo;

public:
    FadeLedAnimation(RgbLed& led, ColorRgb const& from, ColorRgb const& to) : mLed(led), mFrom(from), mTo(to) {}

    void perform(long currTime, long totalTime, int repeatCount) const override;
};

class FadeInLedAnimation : public Animation
{
    RgbLed& mLed;
    ColorRgb mColor;

public:
    FadeInLedAnimation(RgbLed& led, ColorRgb const& color) : mLed(led), mColor(color) {}

    void perform(long currTime, long totalTime, int repeatCount) const override;
};

class FadeOutLedAnimation : public Animation
{
    RgbLed& mLed;
    ColorRgb mColor;

public:
    FadeOutLedAnimation(RgbLed& led, ColorRgb const& color) : mLed(led), mColor(color) {}

    void perform(long currTime, long totalTime, int repeatCount) const override;
};

class PowerOnLedAnimation : public Animation
{
    RgbLed& mLed;
    ubyte mHueOffset = 0;
    ubyte mSaturation = 255;
    ubyte mValue = 255;

public:
    PowerOnLedAnimation(RgbLed& led, ubyte hueOffset) : mLed(led), mHueOffset(hueOffset) {}

    void perform(long currTime, long totalTime, int repeatCount) const override;
};

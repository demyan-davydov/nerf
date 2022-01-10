#pragma once

#include "ColorRgb.h"

class RgbLed
{
public:
    RgbLed(int pinR, int pinG, int pinB);

    void color(int r, int g, int b);

    void color(ColorRgb const& c);

    inline ColorRgb const& color() const { return mColor; }

private:
    int mPinR = 0;
    int mPinG = 0;
    int mPinB = 0;

    ColorRgb mColor;
};
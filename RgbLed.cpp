#include "RgbLed.h"

#include "DrivenByMinus.h"

#include <Arduino.h>


using Pin = DrivenByMinus;

RgbLed::RgbLed(int pinR, int pinG, int pinB)
: mPinR(pinR)
, mPinG(pinG)
, mPinB(pinB)
{
    pinMode(pinR, OUTPUT);
    pinMode(pinG, OUTPUT);
    pinMode(pinB, OUTPUT);

    color(0, 0, 0);
}

void RgbLed::color(int r, int g, int b)
{
    Pin::writePWM(mPinR, r);
    Pin::writePWM(mPinG, g);
    Pin::writePWM(mPinB, b);
}

void RgbLed::color(ColorRgb const& c)
{
    color(c.r, c.g, c.b);
}


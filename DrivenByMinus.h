#pragma once

#include <Arduino.h>

// katonde driven Pin
class DrivenByMinus
{
    DrivenByMinus();

public:
    inline static void writePWM(int pin, int v)
    {
        analogWrite(pin, 255 - v);
    }

    inline static void writeLevel(int pin, int v)
    {
        digitalWrite(pin, 1 - v);
    }
};

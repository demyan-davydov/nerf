#pragma once

#include <Arduino.h>

// Anod driven Pin
class DrivenByPlus
{
    DrivenByPlus();

public:
    inline static void writePWM(int pin, int v)
    {
        analogWrite(pin, v);
    }

    inline static void writeLevel(int pin, int v)
    {
        digitalWrite(pin, v);
    }
};

#include "Vibro.h"

#include "DrivenByMinus.h"

#include "Arduino.h"


using Pin = DrivenByMinus;


Vibro::Vibro(int pin)
: mPin(pin)
{
    pinMode(mPin, OUTPUT);
    speed(0);
}

void Vibro::speed(int speed)
{
    Pin::writePWM(mPin, speed);
}

void Vibro::stop()
{
    speed(0);
}

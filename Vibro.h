#pragma once


class Vibro
{
public:
    Vibro(int pin);

    //! Sets speed [0..255]
    void speed(int speed);

    void stop();

private:
    int mPin = 0;
};
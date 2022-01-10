#include "RgbLed.h"
#include "Vibro.h"
#include "Switcher.h"
#include "AnimationsController.h"
#include "AnimationsForLed.h"
#include "AnimationsForVibro.h"

//#define LED_PIN 13

RgbLed led(5, 6, 9);
Vibro vibro(3);
Switcher switcher(8);
AnimationsController animations;

//long currTime = micros();

void playPowerOnAnimations()
{
    animations.since(micros())
        .add(80, new FadeOnLedAnimation(led, ColorRgb(0, 150, 150)))
        .pause(80)
        .add(80, new FadeOffLedAnimation(led, ColorRgb(0, 150, 150)));

    while(!animations.empty())
    {
        animations.process(micros());
    }

    delay(100);
}

void setup()
{
    playPowerOnAnimations();
}

void loop()
{
    long currTime = micros();
  
    if (switcher.checkChanges(currTime))
    {
        const bool noAmmo = switcher.state() == Switcher::On;
    
        animations.clear();
        
        if (noAmmo)
        {
            const auto vibroTime = currTime + 300 * 1000; // vibro since 300ms
            
            animations.add(vibroTime, 200, new BecomeEmptyVibroAnimation(vibro), 4);
            animations.add(currTime, 250, new BecomeEmptyLedAnimation(led), 3);
        }
        else // have Ammo
        {
            animations.add(currTime, 100, new BecomeFullVibroAnimation(vibro), 3);
            animations.add(currTime, 300, new BecomeFullLedAnimation(led), 2);
        }
    }
  
    animations.process(currTime);
}

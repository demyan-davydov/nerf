#include "RgbLed.h"
#include "Vibro.h"
#include "Switcher.h"
#include "AnimationsController.h"
#include "AnimationsForLed.h"
#include "AnimationsForVibro.h"

RgbLed led(5, 6, 9);
Vibro vibro(3);
Switcher switcher(8, 200);
AnimationsController animations;

void playPowerOnAnimations()
{
    animations.since(micros())
        .add(80, new FadeInLedAnimation(led, ColorRgb(0, 150, 150)))
        .pause(80)
        .add(80, new FadeOutLedAnimation(led, ColorRgb(0, 150, 150)));

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
            animations.since(currTime + 150 * 1000)
                .add(300, new VibroAnimation(vibro, 255)).pause(50)
                .add(200, new VibroAnimation(vibro, 127))
                .add(50, new VibroAnimation(vibro, 0))
                .add(200, new VibroAnimation(vibro, 127))
                .add(0, new VibroAnimation(vibro, 0));

            const ColorRgb clr(255, 0, 0);
            animations.since(currTime)
                .add(250, new FadeInLedAnimation(led, clr)).pause(100)
                .add(100, new FadeInLedAnimation(led, clr)).pause(50)
                .add(100, new FadeInLedAnimation(led, clr));
        }
        else // have Ammo
        {
            animations.since(currTime + 300 * 1000)
              .add(150, new VibroAnimation(vibro, 63))
              .add(150, new VibroAnimation(vibro, 127))
              .add(150, new VibroAnimation(vibro, 255))
              .add(10, new VibroAnimation(vibro, 0));
            
            const ColorRgb clr(0, 255, 0);            
            animations.since(currTime)
                .add(150, new FadeInLedAnimation(led, clr)).pause(100)
                .add(250, new FadeInLedAnimation(led, clr));
        }
    }
  
    animations.process(currTime);
}

#include "ColorRgb.h"

#include <math.h>
#include <stdlib.h>

// Use Adobe formula to calculate brightness (Y)
// Y = 0.212*R + 0.701*G + 0.087*B
int ColorRgb::gray() const
{
    // scale coefficients from range [0..1] to [0..1024]
    const int kR = 217; // 0.212 * 1024
    const int kG = 718; // 0.701 * 1024
    const int kB = 89; // 0.087 * 1024

    int y = (kR*r + kG*g + kB*b) >> 10;

    return y;
}

ColorRgb ColorRgb::fromHsv(float H, float S, float V) // static
{
    H = H > 0 ? fmod(H, 360.f) : 360.f + fmod(H, 360.f);

    // invalid input
    if (S > 100 || S < 0 || V > 100 || V < 0)
    {
        return ColorRgb();
    }

    float s = S/100;
    float v = V/100;
    float C = s*v;
    float X = C*(1-abs(fmod(H/60.0, 2)-1));
    float m = v-C;
    float r,g,b;
    if(H >= 0 && H < 60){
        r = C,g = X,b = 0;
    }
    else if(H >= 60 && H < 120){
        r = X,g = C,b = 0;
    }
    else if(H >= 120 && H < 180){
        r = 0,g = C,b = X;
    }
    else if(H >= 180 && H < 240){
        r = 0,g = X,b = C;
    }
    else if(H >= 240 && H < 300){
        r = X,g = 0,b = C;
    }
    else{
        r = C,g = 0,b = X;
    }

    int R = (r+m)*255;
    int G = (g+m)*255;
    int B = (b+m)*255;

    return ColorRgb(R, G, B);
}

ColorRgb ColorRgb::fromIntHsv(ubyte h, ubyte s, ubyte v)
{
    ColorRgb rgb;
    ubyte region, remainder, p, q, t;

    if (s == 0)
    {
        rgb.r = v;
        rgb.g = v;
        rgb.b = v;
        return rgb;
    }

    region = h / 43;
    remainder = (h - (region * 43)) * 6; 

    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
        case 0:
            rgb.r = v; rgb.g = t; rgb.b = p;
            break;
        case 1:
            rgb.r = q; rgb.g = v; rgb.b = p;
            break;
        case 2:
            rgb.r = p; rgb.g = v; rgb.b = t;
            break;
        case 3:
            rgb.r = p; rgb.g = q; rgb.b = v;
            break;
        case 4:
            rgb.r = t; rgb.g = p; rgb.b = v;
            break;
        default:
            rgb.r = v; rgb.g = p; rgb.b = q;
            break;
    }

    return rgb;
}

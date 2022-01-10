#pragma once

#include "types.h"

// @todo: move to separate file
struct ColorRgb
{
    ColorRgb() : r(0), g(0), b(0)
    {}

    ColorRgb(int r, int g, int b) : r(r), g(g), b(b)
    {}

    inline void gray(int y)
    {
        r = g = b = y;
    }

    //! Use Adobe formula to calculate brightness (Y)
    //! Y = 0.212*R + 0.701*G + 0.087*B
    int gray() const;

    // h : [0..360]
    // s : [0..100]
    // v : [0..100]
    static ColorRgb fromHsv(float h, float s, float v);

    // h : [0..255]
    // s : [0..255]
    // v : [0..255]
    static ColorRgb fromIntHsv(ubyte h, ubyte s, ubyte v);

    int r = 0;
    int g = 0;
    int b = 0;
};


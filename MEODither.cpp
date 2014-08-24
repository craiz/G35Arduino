/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz
  and Adafruit

  See README for complete attributions.
*/

#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_MEODITHER
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <MEODither.h>

#define PATTERN_COUNT 8

MEODither::MEODither(G35& g35)
  : LightProgram(g35),
    intensity_(0),
    colorMain_(0),
    step_(0)
{
    DebugPrintf("MEODither\n");

    pattern_count_ = PATTERN_COUNT;
}

uint32_t MEODither::Do()
{
    switch (pattern_ % 8)
    {
    case 0:
        colorMain_ = COLOR(15,0,0);
        break;
    case 1:
        colorMain_ = COLOR(11,0,3);
        break;
    case 2:
        colorMain_ = COLOR(7,0,7);
        break;
    case 3:
        colorMain_ = COLOR(3,0,11);
        break;
    case 4:
        colorMain_ = COLOR(0,0,15);
        break;
    case 5:
        colorMain_ = COLOR(3,0,11);
        break;
    case 6:
        colorMain_ = COLOR(7,0,7);
        break;
    case 7:
        colorMain_ = COLOR(11,0,3);
        break;
    }

    // Determine highest bit needed to represent pixel index
    int hiBit = 0;
    int n = light_count_ - 1;
    for(int bit = 1; bit < 0x8000; bit <<= 1)
    {
        if(n & bit) hiBit = bit;
    }

    int bit, reverse;

    // Reverse the bits in i to create ordered dither:
    reverse = 0;
    for(bit = 1; bit <= hiBit; bit <<= 1)
    {
        reverse <<= 1;
        if(step_ & bit)
        {
            reverse |= 1;
        }
    }
    g35_.set_color(reverse, G35::MAX_INTENSITY, colorMain_);

    step_++;
    if (step_ == (hiBit << 1))
    {
        step_ = 0;
        pattern_++;
    }

    return delay_;
}
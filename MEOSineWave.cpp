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
#if DEBUG_LIGHT_PROGRAM_MEOSINEWAVE
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <MEOSineWave.h>
#include <RainbowUtils.h>

#define PATTERN_COUNT 7

MEOSineWave::MEOSineWave(G35& g35)
  : LightProgram(g35),
    colorMain_(COLOR(0,0,15)),
    colorHi_(COLOR(12,12,12)),
    colorLo_(COLOR(0,0,0)),
    wavesPerString_(2),
    rainbowMain_(true),
    step_(0),
    step2_(0)
{
    DebugPrintf("MEOSineWave\n");

    pattern_count_ = PATTERN_COUNT;
}

#define PI 3.14159265

uint32_t MEOSineWave::Do()
{
    switch (pattern_ % 7)
    {
    case 0:
        rainbowMain_ = false;
        colorMain_ = COLOR(15,0,0);
        break;
    case 1:
        rainbowMain_ = false;
        colorMain_ = COLOR(0,15,0);
        break;
    case 2:
        rainbowMain_ = false;
        colorMain_ = COLOR(0,0,15);
        break;
    case 3:
        rainbowMain_ = false;
        colorMain_ = COLOR(8,8,0);
        break;
    case 4:
        rainbowMain_ = false;
        colorMain_ = COLOR(8,0,8);
        break;
    case 5:
        rainbowMain_ = false;
        colorMain_ = COLOR(0,8,8);
        break;
    case 6:
        rainbowMain_ = true;
        break;
    }

    float y;
    byte  rMain, gMain, bMain, rOut, gOut, bOut, rhi, ghi, bhi, rlo, glo, blo, rRainbow, gRainbow, bRainbow;

    // Need to decompose colors into their r, g, b elements
    bMain = (colorMain_ >> 8) & 0xf;
    gMain = (colorMain_ >>  4) & 0xf;
    rMain =  colorMain_        & 0xf;

    bhi = (colorHi_ >> 8) & 0xf;
    ghi = (colorHi_ >>  4) & 0xf;
    rhi =  colorHi_        & 0xf;

    blo = (colorLo_ >> 8) & 0xf;
    glo = (colorLo_ >>  4) & 0xf;
    rlo =  colorLo_        & 0xf;

    color_t colorRainbow = GetWheelColor(step2_ % 48);

    bRainbow = (colorRainbow >> 8) & 0xf;
    gRainbow = (colorRainbow >>  4) & 0xf;
    rRainbow =  colorRainbow  & 0xf;

    for(light_count_t i = 0; i < light_count_; i++)
    {
        y = sin(PI * wavesPerString_ * (float)(step_ + i) / (float)light_count_);
        if(y >= 0.0)
        {
            // Peaks of sine wave are white
            y  = 1.0 - y; // Translate Y to 0.0 (top) to 1.0 (center)
            if (rainbowMain_)
            {
                rOut = rhi - (byte)((float)(rhi - rRainbow) * y);
                gOut = ghi - (byte)((float)(ghi - gRainbow) * y);
                bOut = bhi - (byte)((float)(bhi - bRainbow) * y);
            }
            else
            {
                rOut = rhi - (byte)((float)(rhi - rMain) * y);
                gOut = ghi - (byte)((float)(ghi - gMain) * y);
                bOut = bhi - (byte)((float)(bhi - bMain) * y);
            }
        }
        else
        {
            // Troughs of sine wave are black
            y += 1.0; // Translate Y to 0.0 (bottom) to 1.0 (center)
            if (rainbowMain_)
            {
                rOut = rlo + (byte)((float)(rRainbow) * y);
                gOut = glo + (byte)((float)(gRainbow) * y);
                bOut = blo + (byte)((float)(bRainbow) * y);
            }
            else
            {
                rOut = rlo + (byte)((float)(rMain) * y);
                gOut = glo + (byte)((float)(gMain) * y);
                bOut = blo + (byte)((float)(bMain) * y);
            }
        }
        g35_.fill_color(i, 1, G35::MAX_INTENSITY, COLOR(rOut, gOut, bOut));
    }

    step_++;
    step2_++;
    if (step2_ == 48) // all 48 colors in the wheel
    {
        step2_ = 0;
    }

    return delay_;
}
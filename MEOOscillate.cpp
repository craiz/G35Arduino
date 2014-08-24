/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright � 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz
  and Adafruit

  See README for complete attributions.
*/

#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_MEOOSCILLATE
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <MEOOscillate.h>

#define PATTERN_COUNT 4;

MEOOscillate::MEOOscillate(G35& g35)
  : LightProgram(g35),
    intensity_(0),
    colorMain_(0),
    wait_(5),
    oscillations_(10),
    decay_(0.2),
    step_(0)
{
    DebugPrintf("MEOOscillate\n");

    pattern_count_ = PATTERN_COUNT;
}

uint32_t MEOOscillate::Do()
{
    switch (pattern_ % 4)
    {
    case 0:
        colorMain_ = COLOR(12,12,12);
        break;
    case 1:
        colorMain_ = COLOR(0,0,15);
        break;
    case 2:
        colorMain_ = COLOR(15,0,0);
        break;
    case 3:
        colorMain_ = COLOR(0,15,0);
        break;
    }

    float freq = 1; //oscillations per second 
    int amplitude = (light_count_ / 2) - 1; 
    int y;

    float time = float(step_) / 100.0;
    y = (amplitude * sin(freq * time * 2 * PI) / exp(decay_ * time)) + (light_count_ / 2);
    
    if (step_ == 0)
    {
        g35_.fill_color(0, light_count_, G35::MAX_INTENSITY, COLOR_BLACK);
    }
    
    g35_.fill_color(y, 1, G35::MAX_INTENSITY, colorMain_);
    delay(wait_);
    g35_.fill_color(y, 1, G35::MAX_INTENSITY, COLOR_BLACK);

    step_++;
    if (step_ == oscillations_ * 100)
    {
        step_ = 0;
    }
    return delay_;
}
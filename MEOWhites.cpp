/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz

  See README for complete attributions.
*/

#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_MEOWHITES
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <MEOWhites.h>

#define PATTERN_COUNT 3

MEOWhites::MEOWhites(G35& g35)
  : LightProgram(g35),
    intensity_(0)
{
    DebugPrintf("MEOWhites\n");

    pattern_count_ = PATTERN_COUNT;
}

bool MEOWhites::Initialize(pattern_t pattern, uint8_t option, delay_t delay)
{
    LightProgram::Initialize(pattern, option, delay);

    switch (pattern_ % PATTERN_COUNT)
    {
    case 0:
        g35_.fill_color(0, light_count_, 0, COLOR_WARMWHITE);
        break;
    case 1:
        g35_.fill_color(0, light_count_, 0, COLOR_WHITE);
        break;
    case 2:
        for (light_count_t i = 0; i < light_count_; i++)
        {
            if ((i % 2) == 0)
            {
                g35_.fill_color(i, 1, 0, COLOR_WHITE);
            }
            else
            {
                g35_.fill_color(i, 1, 0, COLOR_WARMWHITE);
            }
        }
        break;
    }
    return true;
}

uint32_t MEOWhites::Do()
{
    if (intensity_ <= G35::MAX_INTENSITY)
    {
        g35_.broadcast_intensity(intensity_++);
    }
    return delay_;
}
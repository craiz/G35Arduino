/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  See README for complete attributions.
*/

#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_TWINKLE
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <Twinkle.h>

Twinkle::Twinkle(G35& g35)
  : LightProgram(g35)
{
    DebugPrintf("Twinkle\n");
}

bool Twinkle::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    LightProgram::Initialize(pattern, option, delay);

    g35_.fill_random_max(0, light_count_, G35::MAX_INTENSITY);
    return true;
}

uint32_t Twinkle::Do()
{
    g35_.set_color(rand() % light_count_, G35::MAX_INTENSITY, G35::max_color(rand()));
    return delay_;
}

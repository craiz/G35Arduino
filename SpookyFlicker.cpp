/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  See README for complete attributions.
*/

#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_SPOOKYFLICKER
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <SpookyFlicker.h>

SpookyFlicker::SpookyFlicker(G35& g35)
  : LightProgram(g35),
    intensities_(NULL),
    deltas_(NULL)
{
    DebugPrintf("SpookyFlicker\n");

    delay_default_ = 10;
}

bool SpookyFlicker::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    LightProgram::Initialize(pattern, option, delay);

    intensities_ = static_cast<uint8_t*>(malloc(light_count_ * sizeof(uint8_t)));
    deltas_ = static_cast<int8_t*>(malloc(light_count_ * sizeof(int8_t)));
    if (intensities_ == NULL || deltas_ == NULL)
    {
        return false;
    }
    
    for (light_count_t i = 0; i < light_count_; ++i)
    {
        intensities_[i] = rand();
        deltas_[i] = rand() % 5 - 2;
    }
    g35_.fill_color(0, light_count_, 255, COLOR_BLACK);
    return true;
}

SpookyFlicker::~SpookyFlicker()
{
    free(intensities_);
    free(deltas_);
}

uint32_t SpookyFlicker::Do()
{
    for (light_count_t i = 0; i < light_count_; ++i)
    {
        g35_.set_color(i, intensities_[i], COLOR_ORANGE);
        intensities_[i] += deltas_[i];
    }
    return delay_;
}

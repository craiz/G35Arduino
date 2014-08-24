/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  See README for complete attributions.
*/

#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_CREEPERS
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif


#include <Creepers.h>

Creepers::Creepers(G35& g35) : 
    LightProgram(g35),
    count_(0),
    next_worm_(0)
{
    DebugPrintf("Creepers\n");
}

bool Creepers::Initialize(pattern_t pattern, uint8_t option, delay_t delay)
{
    LightProgram::Initialize(pattern, option, delay);

    g35_.fill_color(0, light_count_, 255, COLOR_BLACK);
    return true;
}

uint32_t Creepers::Do()
{
    for (int i = 0; i < count_; ++i)
    {
        worms_[i].Do(g35_);
    }
    if (count_ < 6 && millis() > next_worm_)
    {
        ++count_;
        worms_[count_ - 1].set_color(rand() & 1 ? COLOR_GREEN : COLOR_ORANGE);
        next_worm_ = millis() + 2000 + 1000 * count_;
    }
    return delay_;
}

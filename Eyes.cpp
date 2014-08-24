/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2012 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  See README for complete attributions.
*/

#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_EYES
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <Eyes.h>

Eyes::Eyes(G35& g35) : 
    LightProgram(g35),
    count_(0),
    next_eye_(0),
    eye_count_(EYE_COUNT)
{
    DebugPrintf("Eyes\n");
}

bool Eyes::Initialize(uint8_t pattern, uint8_t option, delay_t delay)
{
    LightProgram::Initialize(pattern, option, delay);

    g35_.fill_color(0, light_count_, 255, COLOR_BLACK);
    
    if (3 * eye_count_ >= light_count_)
    {
        // There isn't enough room on the light string for this many eyes.
        eye_count_ = light_count_ / 3;
        DebugPrintf("Too many eyes, reducing to %u\n", eye_count_);
    }
    
    for (int i = 0; i < eye_count_; ++i)
    {
        light_count_t new_position;
        do
        {
            new_position = rand() % (light_count_ - 1);
            for (int j = 0; j < i; ++j)
            {
                light_count_t occupied_position = eyes_[j].get_position();
                if (new_position >= occupied_position - 1 &&
                    new_position <= occupied_position + 1)
                {
                    new_position = light_count_;
                    break;
                }
            }
        }
        while (new_position == light_count_);
        eyes_[i].set_position(new_position);
    }
    return true;
}

uint32_t Eyes::Do()
{
    for (int i = 0; i < count_; ++i)
    {
        eyes_[i].Do(g35_);
    }
    if (count_ < eye_count_ && millis() > next_eye_)
    {
        ++count_;
        next_eye_ = millis() + 2000 + 1000 * count_;
    }
    return delay_;
}

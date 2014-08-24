/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2012 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.
  Programs referenced in MEOPrograms by Mark Ortiz <github.com/MarkEMarkEMark>.
  Portions adapted from Adafruit.

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_PROGRAMS_RAINBOW_H
#define INCLUDE_G35_PROGRAMS_RAINBOW_H

#include <LightProgram.h>

class Rainbow : public LightProgram
{
public:
    Rainbow(G35& g35);

    uint32_t Do();
    void Update(pattern_t pattern, option_t option, delay_t delay);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);

private:

    void SetBulb(light_count_t bulb);

    light_count_t active_bulb_count_;
    int8_t color_position_;
    int8_t color_increment_;
    uint8_t palette_size_;
};

#endif


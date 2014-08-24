/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2012 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_PROGRAMS_MEO_OSCILLATE_H
#define INCLUDE_G35_PROGRAMS_MEO_OSCILLATE_H

#include <LightProgram.h>

class MEOOscillate : public LightProgram
{
public:
    MEOOscillate(G35& g35);
    uint32_t Do();

private:
    uint8_t intensity_;
    color_t colorMain_;
    delay_t wait_;
    float decay_;
    uint16_t oscillations_;
    uint16_t step_;
};

#endif
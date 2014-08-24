/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2012 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_PROGRAMS_MEO_WHITES_H
#define INCLUDE_G35_PROGRAMS_MEO_WHITES_H

#include <LightProgram.h>

class MEOWhites : public LightProgram
{
public:
    MEOWhites(G35& g35);
    bool Initialize(pattern_t pattern, uint8_t option, delay_t delay);
    uint32_t Do();

private:
    uint8_t intensity_;
};

#endif
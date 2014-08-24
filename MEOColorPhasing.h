/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright � 2012 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz
  and Adafruit

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_PROGRAMS_MEO_COLORPHASING_H
#define INCLUDE_G35_PROGRAMS_MEO_COLORPHASING_H

#include <LightProgram.h>

class MEOColorPhasing : public LightProgram
{
public:
    MEOColorPhasing(G35& g35);
    uint32_t Do();

private:
    float frequencyR_;
    float frequencyG_;
    float frequencyB_;
    float phaseR_;
    float phaseG_;
    float phaseB_;
    uint8_t center_;
    uint8_t width_;
    int fStep_;
    int pStep_;
    bool fForward_;
    uint8_t turn_;
};

#endif
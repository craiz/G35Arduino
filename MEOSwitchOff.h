/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2012 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz
  and Adafruit

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_PROGRAMS_MEO_SWITCHOFF_H
#define INCLUDE_G35_PROGRAMS_MEO_SWITCHOFF_H

#include <LightProgram.h>

class MEOSwitchOff : public LightProgram
{
public:
    MEOSwitchOff(G35& g35);
    uint32_t Do();

private:
    uint8_t m_Intensity;
};

#endif
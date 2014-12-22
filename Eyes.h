/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2012 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  See README for complete attributions.


  This light program creates an effect of randomly blinking eyes across a light string.
*/

#ifndef INCLUDE_G35_PROGRAMS_EYES_H
#define INCLUDE_G35_PROGRAMS_EYES_H

#include <LightProgram.h>
#include <Eye.h>

class Eyes : public LightProgram
{
public:
    Eyes(G35& g35);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    uint32_t Do();

private:
    enum { EYE_COUNT = 10 };

    uint8_t count_;
    uint32_t next_eye_;
    Eye eyes_[EYE_COUNT];
    uint8_t eye_count_;
};


#endif  // INCLUDE_G35_PROGRAMS_EYES_H

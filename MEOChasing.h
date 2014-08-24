/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2012 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_PROGRAMS_MEO_CHASING_H
#define INCLUDE_G35_PROGRAMS_MEO_CHASING_H

#include <LightProgram.h>

class MEOChasing : public LightProgram
{
public:
    MEOChasing(G35& g35);
    uint32_t Do();

private:
    static color_t PastelRGB(sequence_t sequence);
    static color_t RGBY(sequence_t sequence);
    static color_t RWB(sequence_t sequence);
    static color_t RC(sequence_t sequence);
    static color_t GM(sequence_t sequence);
    static color_t BY(sequence_t sequence);
    static color_t RG(sequence_t sequence);
    static color_t GB(sequence_t sequence);
    static color_t BR(sequence_t sequence);
    static color_t CM(sequence_t sequence);
    static color_t MY(sequence_t sequence);
    static color_t YC(sequence_t sequence);
    static color_t RGB(sequence_t sequence);
    static color_t CYM(sequence_t sequence);
    static color_t RCGMBY(sequence_t sequence);
    static color_t PurplyBlue(sequence_t sequence);
    static color_t Valentines(sequence_t sequence);
    static color_t BlueTriad(sequence_t sequence);
    static color_t BlueBronze(sequence_t sequence);
    static color_t BlueTetrad(sequence_t sequence);
    static color_t PurpleTetrad(sequence_t sequence);
    static color_t GreenTetrad(sequence_t sequence);
    static color_t GreenAccentedAlalogic(sequence_t sequence);
    static color_t RedAccentedAlalogic(sequence_t sequence);
    static color_t BlueAccentedAlalogic(sequence_t sequence);
    
    light_count_t count_;
    sequence_t sequence_;
};

#endif
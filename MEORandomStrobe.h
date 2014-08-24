/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2012 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_PROGRAMS_MEO_RANDOM_STROBE_H
#define INCLUDE_G35_PROGRAMS_MEO_RANDOM_STROBE_H

#include <LightProgram.h>


typedef enum
{
    RANDOM_STROBE_PATTERN_BLACK_WHITE = 0,
    RANDOM_STROBE_PATTERN_BLUE_WHITE = 1,
    RANDOM_STROBE_PATTERN_RED_WHITE = 2,
    RANDOM_STROBE_PATTERN_GREEN_WHITE = 3,
    RANDOM_STROBE_PATTERN_BLACK_RAINBOW_FULL = 4,
    RANDOM_STROBE_PATTERN_BLACK_RAINBOW = 5,
    RANDOM_STROBE_PATTERN_RAINBOW_WHITE_FULL = 6,
    RANDOM_STROBE_PATTERN_RAINBOW_WHITE = 7,
    RANDOM_STROBE_PATTERN_RAINBOW_RAINBOW_FULL = 8,
    RANDOM_STROBE_PATTERN_RAINBOW = 9,
    RANDOM_STROBE_PATTERN_YELLOW_WHITE = 10,

    RANDOM_STROBE_PATTERN_COUNT
    
} RANDOM_STROBE_PATTERNS;

class MEORandomStrobe : public LightProgram
{
public:
    MEORandomStrobe(G35& g35);
    virtual ~MEORandomStrobe();
    void RandomizeStrobe();
    bool Initialize(pattern_t pattern, uint8_t option, delay_t delay);
    void Update(pattern_t pattern, uint8_t option, delay_t delay);
    uint32_t Do();

private:
    bool preFill_;
    light_count_t preFillBulb_;
    bool strobe_;
    uint8_t wait_;
    uint8_t noAtATime_;
    color_t colorMain_;
    color_t colorFlash_;
    bool rainbowFlash_; //instead of single strobe color, will cycle through colour wheel
    bool rainbowMain_; //instead of single background color, will cycle through colour wheel (complimentary colour to flash)
    bool rainbowFrame_; //if rainbow flash, then whether cycles colour after all bulbs flashed or with each bulb flashed
    sequence_t step_;
    light_count_t myBulb_;
    light_count_t* mySequence_;
};

#endif
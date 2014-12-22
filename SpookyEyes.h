/*
  This light program creates an effect of randomly blinking eyes.
  It is designed to run on a customized light string where each bulb
  is attached to a prop which looks like a set of eyes.
*/

#ifndef INCLUDE_G35_PROGRAMS_SPOOKY_EYES_H
#define INCLUDE_G35_PROGRAMS_SPOOKY_EYES_H

#include <LightProgram.h>
#include <Eye.h>

class SpookyEyes : public LightProgram
{
public:
    SpookyEyes(G35& g35);
    ~SpookyEyes();
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    void Update(pattern_t pattern, option_t option, delay_t delay);
    uint32_t Do();

    enum
    {
        ANGRY,
        CALM
    };

private:

    uint32_t next_eye_time_;
    light_count_t active_eye_count_;
    Eye *eyes_;
};


#endif  // INCLUDE_G35_PROGRAMS_SPOOKY_EYES_H
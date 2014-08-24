#ifndef INCLUDE_G35_PROGRAMS_CONTROLLER_RAINBOW_CHASE_H
#define INCLUDE_G35_PROGRAMS_CONTROLLER_RAINBOW_CHASE_H

#include <LightProgram.h>


class ControllerProgramRainbowChase : public LightProgram
{
public:
    ControllerProgramRainbowChase(G35& g35);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    uint32_t Do();

private:

    sequence_t m_sequence;
};

#endif  // INCLUDE_G35_PROGRAMS_CONTROLLER_RAINBOW_CHASE_H


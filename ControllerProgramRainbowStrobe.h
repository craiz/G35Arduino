#ifndef INCLUDE_G35_PROGRAMS_CONTROLLER_RAINBOW_STROBE_H
#define INCLUDE_G35_PROGRAMS_CONTROLLER_RAINBOW_STROBE_H

#include <LightProgram.h>


class ControllerProgramRainbowStrobe : public LightProgram
{
public:
    ControllerProgramRainbowStrobe(G35& g35);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);

private:
};

#endif  // INCLUDE_G35_PROGRAMS_CONTROLLER_RAINBOW_STROBE_H


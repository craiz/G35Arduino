#ifndef INCLUDE_G35_PROGRAMS_CONTROLLER_TWINKLE_H
#define INCLUDE_G35_PROGRAMS_CONTROLLER_TWINKLE_H

#include <LightProgram.h>


class ControllerProgramTwinkle : public LightProgram
{
public:
    ControllerProgramTwinkle(G35& g35);
    bool Initialize(pattern_t pattern, uint8_t option, delay_t delay);

private:

};

#endif  // INCLUDE_G35_PROGRAMS_CONTROLLER_TWINKLE_H


#ifndef INCLUDE_G35_PROGRAMS_CONTROLLER_ALTERNATE_DIRECTION_H
#define INCLUDE_G35_PROGRAMS_CONTROLLER_ALTERNATE_DIRECTION_H

#include <LightProgram.h>


class ControllerProgramAlternateDirection : public LightProgram
{
public:
    ControllerProgramAlternateDirection(G35& g35);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    uint32_t Do();

private:
};

#endif  // INCLUDE_G35_PROGRAMS_CONTROLLER_ALTERNATE_DIRECTION_H


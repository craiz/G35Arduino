#ifndef INCLUDE_G35_PROGRAMS_CONTROLLER_STROBE_H
#define INCLUDE_G35_PROGRAMS_CONTROLLER_STROBE_H

#include <LightProgram.h>


class ControllerProgramStrobe : public LightProgram
{
public:
    ControllerProgramStrobe(G35& g35, pattern_t pattern);
    bool Initialize(pattern_t pattern, uint8_t option, delay_t delay);

private:

};

#endif  // INCLUDE_G35_PROGRAMS_CONTROLLER_HOLLY_H


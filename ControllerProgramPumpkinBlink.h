#ifndef INCLUDE_G35_PROGRAMS_CONTROLLER_PUMPKIN_BLINK_H
#define INCLUDE_G35_PROGRAMS_CONTROLLER_PUMPKIN_BLINK_H

#include <LightProgram.h>


class ControllerProgramPumpkinBlink : public LightProgram
{
public:
    ControllerProgramPumpkinBlink(G35& g35);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    uint32_t Do();

private:

};

#endif  // INCLUDE_G35_PROGRAMS_CONTROLLER_PUMPKIN_BLINK_H



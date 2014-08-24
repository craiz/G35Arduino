#ifndef INCLUDE_G35_PROGRAMS_CONTROLLER_STROBE_FILL_H
#define INCLUDE_G35_PROGRAMS_CONTROLLER_STROBE_FILL_H

#include <LightProgram.h>
#include <ColorNodeCommands.h>


class ControllerProgramStrobeFill : public LightProgram
{
public:
    ControllerProgramStrobeFill(G35& g35);
    bool Initialize(pattern_t pattern, uint8_t option, delay_t delay);

private:

};

#endif  // INCLUDE_G35_PROGRAMS_CONTROLLER_STROBE_FILL_H


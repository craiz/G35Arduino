#ifndef INCLUDE_G35_PROGRAMS_CONTROLLER_CHASE_H
#define INCLUDE_G35_PROGRAMS_CONTROLLER_CHASE_H

#include <LightProgram.h>
#include <ColorNodeCommands.h>


class ControllerProgramChase : public LightProgram
{
public:
    ControllerProgramChase(G35& g35, pattern_t pattern);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);

private:

};

#endif  // INCLUDE_G35_PROGRAMS_CONTROLLER_CHASE_H


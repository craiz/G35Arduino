#ifndef INCLUDE_G35_PROGRAMS_CONTROLLER_SEAHAWKS_H
#define INCLUDE_G35_PROGRAMS_CONTROLLER_SEAHAWKS_H

#include <LightProgram.h>


class ControllerProgramSeahawks : public LightProgram
{
public:
    ControllerProgramSeahawks(G35& g35);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);

private:
};

#endif  // INCLUDE_G35_PROGRAMS_CONTROLLER_SEAHAWKS_H


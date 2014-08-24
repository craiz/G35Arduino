#ifndef INCLUDE_G35_PROGRAMS_CONTROLLER_METEORITE_H
#define INCLUDE_G35_PROGRAMS_CONTROLLER_METEORITE_H

#include <LightProgram.h>


class ControllerProgramMeteorite : public LightProgram
{
public:
    ControllerProgramMeteorite(G35& g35);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);

private:

};

#endif  // INCLUDE_G35_PROGRAMS_CONTROLLER_METEORITE_H


#ifndef INCLUDE_G35_PROGRAMS_CONTROLLER_CANDY_CANE_H
#define INCLUDE_G35_PROGRAMS_CONTROLLER_CANDY_CANE_H

#include <LightProgram.h>
#include <SpiralTreeStars.h>

class ControllerProgramCandyCane : public LightProgram
{
public:
    ControllerProgramCandyCane(G35& g35);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    uint32_t Do();

private:

    SpiralTreeStars m_SpiralTree;
};

#endif  // INCLUDE_G35_PROGRAMS_CONTROLLER_CANDY_CANE_H



#ifndef INCLUDE_G35_PROGRAMS_CONTROLLER_ICE_H
#define INCLUDE_G35_PROGRAMS_CONTROLLER_ICE_H

#include <LightProgram.h>
#include <SpiralTreeStars.h>

class ControllerProgramIce : public LightProgram
{
public:
    ControllerProgramIce(G35& g35);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    uint32_t Do();

private:

    SpiralTreeStars m_SpiralTree;
};

#endif  // INCLUDE_G35_PROGRAMS_CONTROLLER_ICE_H


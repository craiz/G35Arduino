#ifndef INCLUDE_G35_PROGRAMS_CONTROLLER_HOLLY_H
#define INCLUDE_G35_PROGRAMS_CONTROLLER_HOLLY_H

#include <LightProgram.h>
#include <SpiralTreeStars.h>


class ControllerProgramHolly : public LightProgram
{
public:
    ControllerProgramHolly(G35& g35);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    uint32_t Do(void);

private:

    SpiralTreeStars m_SpiralTree;
};

#endif  // INCLUDE_G35_PROGRAMS_CONTROLLER_HOLLY_H


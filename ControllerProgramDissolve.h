#ifndef INCLUDE_G35_PROGRAMS_CONTROLLER_DISSOLVE_H
#define INCLUDE_G35_PROGRAMS_CONTROLLER_DISSOLVE_H

#include <LightProgram.h>


class ControllerProgramDissolve : public LightProgram
{
public:
    ControllerProgramDissolve(G35& g35);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    uint32_t Do();

private:

    uint8_t m_Color1;
    uint8_t m_Color2;
};

#endif  // INCLUDE_G35_PROGRAMS_CONTROLLER_DISSOLVE_H


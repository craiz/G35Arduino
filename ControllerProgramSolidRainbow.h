#ifndef INCLUDE_G35_PROGRAMS_CONTROLLER_SOLID_RAINBOW_H
#define INCLUDE_G35_PROGRAMS_CONTROLLER_SOLID_RAINBOW_H

#include <LightProgram.h>
#include <ColorUtils.h>


class ControllerProgramSolidRainbow : public LightProgram
{
public:
    ControllerProgramSolidRainbow(G35& g35);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    uint32_t Do();

private:
    COLOR_INFO m_colorInfo;
};

#endif  // INCLUDE_G35_PROGRAMS_CONTROLLER_SOLID_RAINBOW_H


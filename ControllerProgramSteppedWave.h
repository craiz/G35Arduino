#ifndef INCLUDE_G35_PROGRAMS_CONTROLLER_STEPPED_WAVE_H
#define INCLUDE_G35_PROGRAMS_CONTROLLER_STEPPED_WAVE_H

#include <LightProgram.h>


class ControllerProgramSteppedWave : public LightProgram
{
public:
    ControllerProgramSteppedWave(G35& g35);
    bool Initialize(uint8_t pattern, uint8_t option, delay_t delay);
    uint32_t Do();

private:

    uint8_t m_lastColor;
};

#endif  // INCLUDE_G35_PROGRAMS_CONTROLLER_STEPPED_WAVE_H


#ifndef INCLUDE_G35_PROGRAMS_CONTROLLER_SPIRAL_STARS_H
#define INCLUDE_G35_PROGRAMS_CONTROLLER_SPIRAL_STARS_H

#include <LightProgram.h>


enum SpiralStarPatterns
{
    SpiralStarPattern_Random = 0,
    SpiralStarPattern_Blue,
    SpiralStarPattern_Red,
    SpiralStarPattern_Green,
};




class ControllerProgramSpiralStars : public LightProgram
{
public:
    ControllerProgramSpiralStars(G35& g35);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    uint32_t Do();

private:

    uint8_t m_StarGap;
    uint8_t m_WaveColor;
    delay_t m_CyclesUntilStar;
    bool m_LeftToRight;
    bool m_WhiteTip;
    uint16_t m_Address;
    uint16_t m_NewStarAddress;
};

#endif  // INCLUDE_G35_PROGRAMS_CONTROLLER_SPIRAL_STARS_H



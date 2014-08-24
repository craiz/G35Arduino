

#ifndef INCLUDE_G35_PROGRAMS_STROBE_FILL_H
#define INCLUDE_G35_PROGRAMS_STROBE_FILL_H

#include <LightProgram.h>
#include <ColorNodeCommands.h>


// Parameters:
// -----------
// Background Color (16-bit)    = ProgramCommand + 0
// Fill Color (16-bit)          = ProgramCommand + 2
// Strobe Color (16-bit)        = ProgramCommand + 4
// Strobe Wait                  = pattern (if 0, no strobe)

class StrobeFill : public LightProgram
{
public:
    StrobeFill(G35& g35, ProgramCommand *pCommand);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    uint32_t Do();

private:
    ProgramCommand *m_pCommand;

    color_t m_BackgroundColor;
    color_t m_FillColor;
    color_t m_StrobeColor;    

    uint8_t m_StrobeWait;

    light_count_t m_CurrentBulb;
    light_count_t m_TargetBulb;
    int m_Increment;

    uint8_t m_Stage;
};

#endif // INCLUDE_G35_PROGRAMS_STROBE_FILL_H
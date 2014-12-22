

#ifndef INCLUDE_G35_PROGRAMS_DRIP_FILL_H
#define INCLUDE_G35_PROGRAMS_DRIP_FILL_H

#include <LightProgram.h>
#include <ColorNodeCommands.h>
#include <ColorUtils.h>

//-----------------
// Program Description
//-----------------
//
// This light program creates a drip effect.  The drip moves down the light string
// and fills up the string.shooting star effect.
//
//-----------
// Parameters
//-----------
// Pattern:
// --------
// Specifies the drip color mode.
// 0 = fill color
// 1 = white
// 2 = black
// 3 = fixed color in extra data (see Drip Color below)
//
// Option:
// -------
// xxsmwrfd
// Bit 1 - Direction (d). If set, backward, otherwise forward.
// Bit 2 - Fill (f).  If set,fill bulbs incrementally.  Otherwise, all bulbs at once.
// Bit 3 - Random (r).  If not set, random colors are chosen for background and fill.
// Bit 4 - Wait (w). If set causes new drips to only occur when an update command is received.
// Bit 5 - Fill mode (m). If set drips flow in both directions.  Otherwise, only one direction.
// Bit 6 - Wait mode (s).  If set, wait occurs per drip.  Otherwise, per cycle.
//
// Fill mode.  Specified by OPTION_5
//  0: one direction
//  1: both directions, back and forth
//
// Wait mode.  Specified by OPTION_6
//  0: per complete cycle
//  1: per drop
// 
// Delay:
// ------
// Sets the base tick rate of the program.
// 
// Background Color:
// -----------------
// Specifies the background color as an encoded color value.
//  Val: ProgramCommand + 0
//
// Fill Color:
// -----------
// Specifies the fill color as an encoded color value.
//  Val: ProgramCommand + 1
//
// Drip Color:
// -----------
// Specifies the drip color as an encoded color value.
// Only used if pattern indicates "fixed color"
//  Val: ProgramCommand + 2
//
// Drip Size:
// ----------
// The number of bulbs used for a drip.
//  Val: ProgramCommand + 3
//
// Fill Size:
// ----------
// The number of bulbs each drip fills up when it hits the target.
//  Val: ProgramCommand + 4
//

class DripFill : public LightProgram
{
public:
    DripFill(G35& g35, ProgramCommand *pCommand);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    uint32_t Do();

private:

    void TranslateColors();

    ProgramCommand *m_pCommand;

    COLOR_INFO m_BackgroundColorInfo;
    COLOR_INFO m_FillColorInfo;
    COLOR_INFO m_DripColorInfo;

    color_t m_BackgroundColor;
    color_t m_FillColor;
    color_t m_DripColor;

    light_count_t m_TargetBulb;
    light_count_t m_Bulb;
    light_count_t m_DoneBulb;
    
    uint8_t m_FillSize;
    uint8_t m_DripSize;

    FILL_MODE m_FillMode;
    WAIT_MODE m_WaitMode;
    bool m_Forward;
};

#endif // INCLUDE_G35_PROGRAMS_DRIP_FILL_H
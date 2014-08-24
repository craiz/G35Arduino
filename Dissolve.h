
#ifndef INCLUDE_G35_PROGRAMS_DISSOLVE_H
#define INCLUDE_G35_PROGRAMS_DISSOLVE_H

#include <LightProgram.h>
#include <WaveUtils.h>
#include <ColorNodeCommands.h>


//-----------------
// Program Description
//-----------------
//
// This light program creates a dissolving/fade effect between two colors.  The effect can occur
// randomly for each bulb or sequentially accross the entire string.
//
//-----------
// Parameters
//-----------
// Pattern:
// -------
//  The two colors to transition between are embedded in the pattern byte.
//
//  iifffbbb
//  bits 1-3: background color (wave color)
//  bits 4-6: foreground color (wave color)
//  bits 7-8: indicate intermediate color (0=none, 1=white, 2=black)
//
//  If backround and foreground colors are both 0, then random colors are chosen.
//
// Option:
// -------
// xxsmwrfd
// Bit 1 - Direction (d). If set, backward, otherwise forward.
// Bit 2 - Fill (f).  If set, fill bulbs incrementally.  Otherwise, all bulbs at once.
// Bit 3 - Random (r).  If not set, random dissolve, otherwise sequential dissolve.
// Bit 4 - Wait (w). If set causes next dissolve to only occur when an update command is received.
// Bit 5 - Fill mode (m). If set sequential dissolve occurs in both directions.  Otherwise, only one direction. (N/A for random)
//
// Fill mode.  Specified by OPTION_5
//  0: one direction
//  1: both directions, back and forth
//
// Delay:
// ------
// Sets the base tick rate of the program.
// 
// Min Tick Rate:
// ------------
// The minimum tick rate for random dissolve. (Default is 0)
//  Val: ProgramCommand + 0
//
// Max Tick Rate:
// -------------
// The maximum tick rate for random dissolve. (Default is 10)
//  Val: ProgramCommand + 1
//
// Cycle Wait:
// ----------
// The wait time after completing a dissolve cycle before starting a new one.
// N/A if wait option is set.
//  Val: ProgramCommand + 2 & 3

#define DEFAULT_MIN_TICK_RATE 0
#define DEFAULT_MAX_TICK_RATE 10
#define DEFAULT_CYCLE_WAIT 1000

typedef struct 
{
    int8_t Position;
    uint8_t TickRate;
    uint8_t RemainingTicks;
} DISSOLVE_INFO;

class Dissolve : public LightProgram
{
public:
    Dissolve(G35& g35, ProgramCommand *pCommand);
    ~Dissolve();
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    void Uninitialize();
    uint32_t Do();

private:

    void UpdateDissolveInfo(DISSOLVE_INFO *pInfo, int8_t increment);
    void RandomizeBulbs();
    void SequentializeBulbs();
    bool SetupWave();

    ProgramCommand *m_pCommand;

    WAVE_INFO m_WaveInfo;
    DISSOLVE_INFO *m_DissolveInfo;
    uint8_t m_Color1;
    uint8_t m_Color2;
    uint8_t m_IntermediateColor;
    bool m_Forward;
    bool m_RandomColors;

    uint8_t m_MinTick;
    uint8_t m_MaxTick;

    FILL_MODE m_FillMode;
    delay_t m_CycleWait;
};

#endif // INCLUDE_G35_PROGRAMS_DISSOLVE_H


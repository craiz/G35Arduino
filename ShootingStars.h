

#ifndef INCLUDE_G35_PROGRAMS_SHOOTING_STARS_H
#define INCLUDE_G35_PROGRAMS_SHOOTING_STARS_H

#include <LightProgram.h>
#include <ColorNodeCommands.h>


//-----------------
// Program Description
//-----------------
//
// This light program creates a shooting star effect.  Each star
// consists of a half-wave fading from full color to black.
//
// The program can run in normal mode or random mode.
//
// Normal Mode
// ------------
// Stars will be generated at fixed intervals with a fixed size, color and speed.
// An update can be used to change the parameters (color, size, speed, interval).
//
// Random Mode
//-------------
// Stars will randomly be generated at random intervals with random colors, speeds and sizes.
//
//-----------
// Parameters
//-----------
// Option:
// sssswrxx
// Bit 2 - White Tip.  If set, the tip of each star is white.  If not set, normal color.
// Bit 3 - Random.  If set, enables Normal Mode. If not set, enables Random Mode.  
// Bit 4 - Wait. If set causes new stars to only be added when an update command is received.
// high 4-bits are speed (1-4)
//
// Pattern:
// ccccssss
// high 4-bits are color (c) (wave colors)
// low 4-bits are size (s) (3-15)
// 
// Delay:
// Sets the base tick rate of the program.
// 
// Tick Gap:
// The number of ticks before a new star is automatically added.
//  Min: ProgramCommand + 0
//  Max: ProgramCommand + 1
//
// Position Gap:
// This is the light gap between automatically added stars.
//  Min: ProgramCommand + 2
//  Max: ProgramCommand + 3
//
// Max Stars:
// This is the maximum number of supported stars
//  Val: ProgramCommand + 4 (default if 0)

typedef struct _STAR {
    bool Active;
    light_count_t Position;
    uint8_t Size;
    uint8_t Color; // Star color
    uint8_t Speed; // Number of ticks per move
    uint8_t TicksRemaining; // Number of ticks until next move.

    _STAR* Next;
} STAR;

class ShootingStars : public LightProgram
{
public:
    ShootingStars(G35& g35, ProgramCommand *pCommand);
    virtual ~ShootingStars();
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    void Update(pattern_t pattern, option_t option, delay_t delay);
    uint32_t Do();
    void Kick();

private:

    void ParseAndValidateParameters();
    bool AddStar(uint8_t color, uint8_t size, uint8_t speed);
    void AddRandomStar(bool fForce);
    void AddNormalStar(bool fForce);
    void UpdateStars();
    void DrawStar(STAR *pStar);

    ProgramCommand *m_pCommand;

    STAR *m_pStars;

    STAR *m_pOldestStar;
    STAR *m_pNewestStar;

    uint8_t m_nMaxStars;
    uint8_t m_nActiveStars;
    uint8_t m_nTopGap;

    uint8_t *m_pBulbBuffer;

    uint8_t m_Color;
    uint8_t m_Size;
    uint8_t m_Speed;

    uint8_t m_TickGapMin;
    uint8_t m_TickGapMax;
    uint8_t m_PositionGapMin;
    uint8_t m_PositionGapMax;

    uint8_t m_TicksUntilAdd;
    uint8_t m_GapUntilAdd;

    bool m_fWhiteTip;
};

#endif // INCLUDE_G35_PROGRAMS_SHOOTING_STARS_H
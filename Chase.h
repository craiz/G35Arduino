/*
 This program creates a chasing effect by sequencing each bulb through a
 configurable color pattern.  The speed and number of bulbs per position in
 the pattern are also configurable.

  By Paul Irwin
*/

#ifndef INCLUDE_G35_PROGRAMS_CHASE_H
#define INCLUDE_G35_PROGRAMS_CHASE_H

#include <LightProgram.h>
#include <ColorNodeCommands.h>
#include <SequenceUtils.h>

// Extra Data Parameters:
// ----------------------
// Bulbs Per Position (8-bit)   = ProgramData + 0
// Color Count (8-bit)          = ProgramData + 1
// Color 1 (16-bit)             = ProgramData + 2
// Color N (16-bit)             = ProgramData + 2 + ((N - 1) * 2)

class Chase : public LightProgram
{
public:
    Chase(G35& g35, ProgramCommand *pCommand);
    virtual ~Chase();
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    void Update(pattern_t pattern, option_t option, delay_t delay);
    uint32_t Do();

private:

    ProgramCommand *m_pCommand;
    SEQUENCE_INFO m_SequenceInfo;
    uint8_t m_ActiveCount;
    sequence_t m_Sequence;
    light_count_t m_Start;
    bool m_Forward;
};

#endif


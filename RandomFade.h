/*
 This program randomly fades each bulb bewteen min/max intensities.
 The color pattern can be configured.

  By Paul Irwin
*/

#ifndef INCLUDE_G35_PROGRAMS_RANDOM_FADE_H
#define INCLUDE_G35_PROGRAMS_RANDOM_FADE_H

#include <LightProgram.h>
#include <ColorNodeCommands.h>
#include <SequenceUtils.h>

class RandomFade : public LightProgram
{
public:
    RandomFade(G35& g35, ProgramCommand *pCommand);
    virtual ~RandomFade();
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    
    uint32_t Do();

private:

    typedef struct
    {
        uint8_t intensity;
        int8_t velocity;
        light_count_t sequence;
    } BulbInfo;

    ProgramCommand *m_pCommand;
    SEQUENCE_INFO m_SequenceInfo;
    BulbInfo *m_bulbs;
    uint8_t m_loopCounter;
    uint8_t m_fadeSpeeds;
    uint8_t m_minIntensity;
};

#endif  // INCLUDE_G35_PROGRAMS_RANDOM_FADE_H
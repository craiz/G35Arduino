/*
 This program creates a chasing effect by sequencing each bulb through a
 configurable color pattern.  The speed and number of bulbs per position in
 the pattern are also configurable.

  By Paul Irwin
*/

#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_CHASE
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <Chase.h>
#include <SequenceUtils.h>

Chase::Chase(G35& g35, ProgramCommand *pCommand)
  : LightProgram(g35)
  , m_pCommand(pCommand)
  , m_Sequence(0)
{
    DebugPrintf("Chase\n");

    delay_default_ = g35_.get_bulb_frame() + 10;
}

Chase::~Chase()
{
    SetActiveSequence(NULL);
}

bool Chase::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    LightProgram::Initialize(pattern, option, delay);

    uint8_t * extraData = (uint8_t *)m_pCommand + sizeof(ProgramCommand);

    m_SequenceInfo.BulbsPerPosition = extraData[0];
    m_SequenceInfo.Size = extraData[1];
    m_SequenceInfo.Colors = (color_t *)&extraData[2];
    SetActiveSequence(&m_SequenceInfo);

    if (IS_FILL_IMMEDIATE(option_))
    {
        m_ActiveCount = g35_.get_light_count();
    }
    else
    {
        m_ActiveCount = 1;
    }

    if (IS_FORWARD(option_))
    {
        m_Start = 0;
        m_Forward = true;
    }
    else
    {
        m_Start = g35_.get_light_count() - 1;
        m_Forward = false;
    }

    return true;
}

uint32_t Chase::Do()
{
    g35_.fill_sequence(m_Forward, m_Start, m_ActiveCount, m_Sequence, m_SequenceInfo.BulbsPerPosition, G35::MAX_INTENSITY, Sequencer);

    if (m_ActiveCount < g35_.get_light_count())
    {
        m_ActiveCount++;
    }
    else
    {
        if (m_Forward)
        {
            m_Sequence++;
        }
        else
        {
            m_Sequence--;
        }

        if (IS_WAIT(option_))
        {
            DebugPrintf("Waiting...\n");
            waiting_ = true;
            return 0;
        }
    }
    return delay_;
}

void Chase::Update(pattern_t pattern, option_t option, delay_t delay)
{
    Initialize(pattern, option, delay);
}


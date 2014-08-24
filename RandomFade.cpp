/*
 This program randomly fades each bulb bewteen min/max intensities.
 The color pattern can be configured.

  By Paul Irwin
*/

#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_RANDOM_FADE
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <RandomFade.h>
#include <SequenceUtils.h>

RandomFade::RandomFade(G35& g35, ProgramCommand *pCommand)
  : LightProgram(g35)
  , m_pCommand(pCommand)
  , m_loopCounter(0)
  , m_bulbs(NULL)
  , m_fadeSpeeds(3)
{
    DebugPrintf("RandomFade\n");

    // Three speeds
    option_default_ = 0x30;
}

RandomFade::~RandomFade()
{
    free(m_bulbs);
}

bool RandomFade::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    LightProgram::Initialize(pattern, option, delay);
    
    m_bulbs = static_cast<BulbInfo*>(malloc(light_count_ * sizeof(BulbInfo)));
    if (m_bulbs == NULL)
    {
        return false;
    }

    uint8_t * extraData = (uint8_t *)m_pCommand + sizeof(ProgramCommand);
    m_SequenceInfo.BulbsPerPosition = 1;
    m_SequenceInfo.Size = extraData[0];
    m_SequenceInfo.Colors = (color_t *)&extraData[1];
    SetActiveSequence(&m_SequenceInfo);

    m_minIntensity = delay;
    if (m_minIntensity >= G35::MAX_INTENSITY)
    {
        m_minIntensity = 0;
    }

    // Get the number of fade speeds from options
    m_fadeSpeeds = option_ >> 4;
    if ((m_fadeSpeeds == 0) || (m_fadeSpeeds > 4))
    {
        m_fadeSpeeds = 3;
    }

    for (light_count_t i = 0; i < light_count_; ++i)
    {
        DebugPrintf("Bulb: %u\n", i);

        m_bulbs[i].sequence = i;
        m_bulbs[i].intensity = m_minIntensity + (rand() % (G35::MAX_INTENSITY - m_minIntensity));
        if (m_bulbs[i].intensity == m_minIntensity)
        {
            m_bulbs[i].intensity = 1;
        }
        m_bulbs[i].velocity = (rand() % m_fadeSpeeds) + 1;
        if ((rand() % 2) == 1)
        {
            m_bulbs[i].velocity *= -1;
        }

        DebugPrintf("  Intensity: %u\n", m_bulbs[i].intensity);
        DebugPrintf("  Velocity: %d\n", m_bulbs[i].velocity);

        g35_.set_color(i, m_bulbs[i].intensity, Sequencer(m_bulbs[i].sequence));
    }
    return true;
}

uint32_t RandomFade::Do()
{
    m_loopCounter++;

    int8_t targetVelocity1 = (m_loopCounter % m_fadeSpeeds) + 1;
    int8_t targetVelocity2 = targetVelocity1 * -1;

    DebugPrintf("Counter: %u\n", m_loopCounter);
    
    for (light_count_t i = 0; i < light_count_; ++i)
    {
        DebugPrintf("  Bulb: %u\n", i);

        if (m_bulbs[i].velocity == targetVelocity1 || m_bulbs[i].velocity == targetVelocity2)
        {
            DebugPrintf("  Old\n");
            DebugPrintf("    Velocity: %d\n", m_bulbs[i].velocity);
            DebugPrintf("    Intensity: %u\n", m_bulbs[i].intensity);
            DebugPrintf("    Sequence: %u\n", m_bulbs[i].sequence);

            // Switch increment if we are at a boundary.  Positive increment becomes negative, and vice versa.
            // Additionally select a new random speed.
            if ((m_bulbs[i].intensity == m_minIntensity) || (m_bulbs[i].intensity >= G35::MAX_INTENSITY))
            {
                if (m_bulbs[i].velocity < 0)
                {
                    m_bulbs[i].velocity = (rand() % m_fadeSpeeds) + 1;
                }
                else
                {
                    m_bulbs[i].velocity = ((rand() % m_fadeSpeeds) + 1) * -1;
                }
            }

            // Advance color sequence if at min intensity.
            if (m_bulbs[i].intensity == m_minIntensity && IS_RANDOM(option_))
            {
                m_bulbs[i].sequence++;
            }

            // Increment intensity up or down
            if (m_bulbs[i].velocity >= 0)
            {
                m_bulbs[i].intensity++;
            }
            else
            {
                m_bulbs[i].intensity--;
            }

            // Update the color of the current bulb.
            g35_.set_color(i, m_bulbs[i].intensity, Sequencer(m_bulbs[i].sequence));

            DebugPrintf("  New\n");
            DebugPrintf("    Velocity: %d\n", m_bulbs[i].velocity);
            DebugPrintf("    Intensity: %u\n", m_bulbs[i].intensity);
            DebugPrintf("    Sequence: %u\n", m_bulbs[i].sequence);
        }
    }

    // Go as fast as possible.  The speed of individual bulb updates are random.
    return 0;
}


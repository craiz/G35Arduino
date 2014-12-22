/*
 This program creates a dissolve effect by transitioning between colors.  Full saturation colors are supported.

  By Paul Irwin
*/

#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_DISSOLVE
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <Dissolve.h>

Dissolve::Dissolve(G35& g35, ProgramCommand *pCommand)
  : LightProgram(g35)
  , m_pCommand(pCommand)
  , m_DissolveInfo(NULL)
  , m_Forward(true)
  , m_RandomColors(false)
  , m_Color1(WAVE_COLOR_BLACK)
  , m_Color2(WAVE_COLOR_BLACK)
  , m_IntermediateColor(WAVE_COLOR_COUNT)
  , m_FillMode(FILL_MODE_ONE_DIRECTION)
  , m_CycleWait(DEFAULT_CYCLE_WAIT)
  , m_MinTick(DEFAULT_MIN_TICK_RATE)
  , m_MaxTick(DEFAULT_MAX_TICK_RATE)
{
    DebugPrintf("Dissolve\n");

    m_WaveInfo.Size = 0;
    m_WaveInfo.Wave = NULL;
}

Dissolve::~Dissolve()
{
    Uninitialize();
}

void Dissolve::Uninitialize()
{
    if (m_DissolveInfo)
    {
        free(m_DissolveInfo);
        m_DissolveInfo = NULL;
    }
    DestroyColorWave(&m_WaveInfo);
}

bool Dissolve::SetupWave(void)
{
    uint8_t count = 0;
    uint8_t holds[3] = {1, 1, 1};
    uint8_t colors[3];

    DebugPrintf("Direction=%s\n", m_Forward ? "Forward" : "Backward");
    DebugPrintf("Color1=%u\n", m_Color1);
    DebugPrintf("Color2=%u\n", m_Color2);
    colors[0] = m_Color1;
    if (m_IntermediateColor == WAVE_COLOR_COUNT)
    {
        // No intermediate color.
        DebugPrintf("Intermediate=None\n");
        count = 2;
    }
    else
    {
        // Set intermediate color.
        DebugPrintf("Intermediate=%u\n", m_IntermediateColor);
        count = 3;
        colors[1] = m_IntermediateColor;
    }
    colors[count - 1] = m_Color2;    

    DestroyColorWave(&m_WaveInfo);
    return CreateColorWave(&m_WaveInfo, count, colors, holds, 15);
}

bool Dissolve::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    DebugPrintf("Initializing...\n");
    Uninitialize();
    LightProgram::Initialize(pattern, option, delay);

    // Get extra options if available.
    if (m_pCommand)
    {
        uint8_t *pExtraOptions = (uint8_t *)m_pCommand + sizeof(ProgramCommand);
        m_MinTick = pExtraOptions[0];
        m_MaxTick = pExtraOptions[1];
        m_CycleWait = *((delay_t *)&pExtraOptions[2]);
    }
    if (m_MaxTick == 0)
    {
        m_MaxTick = DEFAULT_MAX_TICK_RATE;
    }
    if (m_MinTick > m_MaxTick)
    {
        m_MinTick = DEFAULT_MIN_TICK_RATE;
        m_MaxTick = DEFAULT_MAX_TICK_RATE;
    }
    if (m_CycleWait == 0)
    {
        m_CycleWait = DEFAULT_CYCLE_WAIT;
    }

    // Get the colors from the pattern.
    m_Color1 = pattern_ & 0x07;
    m_Color2 = (pattern_ >> 3) & 0x07;
    switch((pattern_ >> 6) & 0x03)
    {
    default:
    case 0: // No intermediate color
        m_IntermediateColor = WAVE_COLOR_COUNT;
        break;
    case 1: // Intermediate white
        m_IntermediateColor = WAVE_COLOR_WHITE;
        break;
    case 2: // Intermediate black
        m_IntermediateColor = WAVE_COLOR_BLACK;
        break;
    }

    // Pick random color if requested.
    if (!m_Color1 && !m_Color2)
    {
        m_RandomColors = true;
        m_Color1 = GetRandomWaveColor(WAVE_COLOR_BLACK, m_IntermediateColor, WAVE_COLOR_BLACK);
        m_Color2 = GetRandomWaveColor(m_Color1, m_IntermediateColor, WAVE_COLOR_BLACK);
    }

    // Get fill mode
    if (option_ & OPTION_BIT_5)
    {
        m_FillMode = FILL_MODE_BOTH_DIRECTIONS;
    }

    // Get initial direction.
    m_Forward = IS_FORWARD(option_);

    if (!SetupWave())
    {
        return false;
    }

    m_DissolveInfo = static_cast<DISSOLVE_INFO*>(malloc(light_count_ * sizeof(DISSOLVE_INFO)));
    if (!m_DissolveInfo)
    {
        DebugPrintf("Failed to allocate DISSOLVE_INFO\n");
        return false;
    }

    if (IS_RANDOM(option_))
    {
        RandomizeBulbs();
    }
    else
    {
        SequentializeBulbs();
    }

    if (IS_FILL_IMMEDIATE(option_))
    {
        if (m_Forward)
        {
            // Set all bulbs to color 1 so they can be disolved to color 2
            g35_.fill_color(0, light_count_, G35::MAX_INTENSITY, m_WaveInfo.Wave[0]);
        }
        else
        {
            // Set all bulbs to color 2 so they can be dissolved to color 1
            g35_.fill_color(0, light_count_, G35::MAX_INTENSITY, m_WaveInfo.Wave[m_WaveInfo.Size - 1]);
        }
    }

    return true;
}

void Dissolve::UpdateDissolveInfo(DISSOLVE_INFO *pInfo, int8_t increment)
{
    if (pInfo->RemainingTicks == 0)
    {
        pInfo->Position += increment;
        pInfo->RemainingTicks = pInfo->TickRate;
    }
    else
    {
        pInfo->RemainingTicks--;
    }
}

void Dissolve::RandomizeBulbs()
{
    // Each bulb will transition across the wave at a random speed.
    for (light_count_t i = 0; i < light_count_; i++)
    {
        if (m_Forward)
        {
            m_DissolveInfo[i].Position = 0;
        }
        else
        {
            m_DissolveInfo[i].Position = m_WaveInfo.Size - 1;
        }
        m_DissolveInfo[i].TickRate = m_MinTick + (rand() % (m_MaxTick - m_MinTick));
        m_DissolveInfo[i].RemainingTicks = m_DissolveInfo[i].TickRate;
    }
}

void Dissolve::SequentializeBulbs()
{
    // A single wave will traverse across the lights.
    for (light_count_t i = 0; i < light_count_; i++)
    {
        if (m_Forward)
        {
            m_DissolveInfo[i].Position = 0 - i;
        }
        else
        {
            m_DissolveInfo[i].Position = ((light_count_ - 1) + (m_WaveInfo.Size - 1)) - i;
        }
        m_DissolveInfo[i].TickRate = 1;
        m_DissolveInfo[i].RemainingTicks = m_DissolveInfo[i].TickRate;
    }
}

uint32_t Dissolve::Do()
{
    light_count_t finishedCount = 0;

    for (light_count_t i = 0; i < light_count_; i++)
    {
        if (m_Forward)
        {
            // Going forward
            if (m_DissolveInfo[i].Position >= (m_WaveInfo.Size - 1))
            {
                finishedCount++;
                if (!IS_RANDOM(option_))
                {
                    // Only increment sequential after the end of the wave is reached.
                    UpdateDissolveInfo(&m_DissolveInfo[i], 1);
                }
            }
            else
            {
                // Always increment random and sequential until the end of the wave is reached.
                UpdateDissolveInfo(&m_DissolveInfo[i], 1);
            }
        }
        else
        {
            // Going backward
            if (m_DissolveInfo[i].Position <= 0)
            {
                finishedCount++;
                if (!IS_RANDOM(option_))
                {
                    // Only decrement sequential after the beginning of the wave is reached.
                    UpdateDissolveInfo(&m_DissolveInfo[i], -1);
                }
            }
            else
            {
                // Always decrement random and sequential until the beginning of the wave is reached.
                UpdateDissolveInfo(&m_DissolveInfo[i], -1);
            }
        }

        if (m_DissolveInfo[i].Position >= 0 && m_DissolveInfo[i].Position < m_WaveInfo.Size)
        {
            g35_.set_color(i, G35::MAX_INTENSITY, m_WaveInfo.Wave[m_DissolveInfo[i].Position]);
        }
    }

    // Check if we should change directions, colors or wait
    if (finishedCount == light_count_)
    {
        // Check if we should pick new random colors or swap the current colors.
        if (m_RandomColors)
        {
            if (m_Forward)
            {
                // Currently showing color 2, pick a new color 1.
                m_Color1 = GetRandomWaveColor(m_Color2, m_IntermediateColor, WAVE_COLOR_BLACK);
            }
            else
            {
                // Currently showing a color 1, pick a new color 2.
                m_Color2 = GetRandomWaveColor(m_Color1, m_IntermediateColor, WAVE_COLOR_BLACK);
            }
        }

        if (m_FillMode == FILL_MODE_ONE_DIRECTION && !IS_RANDOM(option_))
        {
            // Cycle again in the same direction.  Need to swap the colors so the wave
            // begins with the current color and ends in the new one.
            uint8_t temp = m_Color1;
            m_Color1 = m_Color2;
            m_Color2 = temp;
        }

        if (m_FillMode == FILL_MODE_BOTH_DIRECTIONS || IS_RANDOM(option_))
        {
            m_Forward = !m_Forward;
        }
        SetupWave();

        if (IS_RANDOM(option_))
        {
            RandomizeBulbs();
        }
        else if (m_FillMode == FILL_MODE_ONE_DIRECTION)
        {
            SequentializeBulbs();
        }

        if (IS_WAIT(option_))
        {
            DebugPrintf("Waiting...\n");
            waiting_ = true;
        }
        else
        {
            return m_CycleWait;            
        }
    }
    return delay_;
}


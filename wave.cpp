/*
 This program creates a wave effect by transitioning between colors.
 Full saturation colors are supported.

  By Paul Irwin
*/

#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_WAVE
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <Wave.h>


byte *g_colorWavePositions = NULL;
byte g_colorWavePositionCount = 0;
WAVE_INFO g_colorWaveInfo = {0};

color_t WaveSequencer(sequence_t sequence)
{
    return g_colorWaveInfo.Wave[g_colorWavePositions[sequence % g_colorWavePositionCount]];
}

Wave::Wave(G35& g35, ProgramCommand *pCommand)
  : LightProgram(g35)
  , m_pCommand(pCommand)
  , count_(1)
  , m_positionSpan(1)
{
    DebugPrintf("Wave\n");
}

Wave::~Wave()
{
    Uninitialize();
}

void Wave::Uninitialize()
{
    if (g_colorWavePositions)
    {
        free(g_colorWavePositions);
        g_colorWavePositions = NULL;
    }
    g_colorWavePositionCount = 0;

    DestroyColorWave(&g_colorWaveInfo);
}

bool Wave::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    DebugPrintf("Initializing...\n");

    Uninitialize();
    LightProgram::Initialize(pattern, option, delay);

    if (IS_FILL_IMMEDIATE(option_))
    {
        count_ = g35_.get_light_count();
    }
    else
    {
        count_ = 1;
    }

    uint8_t colorCount = pattern;
    uint8_t increments = (option >> 4) & 0x0F;
    uint8_t * extraData = (uint8_t *)m_pCommand + sizeof(ProgramCommand);
    g_colorWavePositionCount = extraData[0];
    uint8_t pixelDistribution = extraData[1];
    m_positionSpan = extraData[2];
    uint8_t *colors = &extraData[3];
    uint8_t *holds = colors + colorCount;

#if DEBUG_ENABLED
    DebugPrintf("Colors: %d\n", colorCount);
    for (byte i = 0; i < colorCount; i++)
    {
        DebugPrintf("  Color%d: %d\n", i, colors[i]);
        DebugPrintf("  Hold%d: %d\n", i, holds[i]);
    }
    DebugPrintf("Increments: %d\n", increments);
    if (m_positionSpan == 0)
    {
        m_positionSpan = 1;
    }
    if (m_positionSpan > g35_.get_light_count())
    {
        m_positionSpan = g35_.get_light_count();
    }
    DebugPrintf("Span Size: %d\n", m_positionSpan);
#endif

    if (!CreateColorWave(&g_colorWaveInfo, colorCount, colors, holds, increments))
    {
        return false;
    }

    // Allocate and set the wave position values
    if (g_colorWavePositionCount == 0 || g_colorWavePositionCount > g_colorWaveInfo.Size)
    {
        g_colorWavePositionCount = g_colorWaveInfo.Size;
    }
    if (g_colorWavePositionCount > g35_.get_light_count())
    {
        g_colorWavePositionCount = g35_.get_light_count();
    }
    DebugPrintf("Wave/Pos: %d/%d\n", g_colorWaveInfo.Size, g_colorWavePositionCount);
    
    g_colorWavePositions = (byte *)malloc(g_colorWavePositionCount);
    if (g_colorWavePositions == NULL)
    {
        DebugPrintf("Failed to allocate positions array\n");
        return false;
    }

    if (pixelDistribution == 0 || pixelDistribution > (g_colorWaveInfo.Size / g_colorWavePositionCount))
    {
        pixelDistribution = g_colorWaveInfo.Size / g_colorWavePositionCount;
    }
    DebugPrintf("Distribution: %d\n", pixelDistribution);
    byte position = 0;
    for (byte i = 0; i < g_colorWavePositionCount; i++)
    {
        g_colorWavePositions[i] = position;
        position += pixelDistribution;
    }

    return true;
}

uint32_t Wave::Do()
{
    uint8_t start = 0;
    bool forward = true;
    bool cycleComplete = false;

    if (!IS_FORWARD(option_))
    {
        start = g35_.get_light_count() - 1;
        forward = false;
    }

    // Apply the current colors
    g35_.fill_sequence(forward, start, count_, 0, m_positionSpan, G35::MAX_INTENSITY, WaveSequencer);

    // Update the sequence positions
    if (forward)
    {
        for (byte i = 0; i < g_colorWavePositionCount; i++)
        {
            g_colorWavePositions[i]++;
            if (g_colorWavePositions[i] >= g_colorWaveInfo.Size)
            {
                if (i == 0)
                {
                    cycleComplete = true;
                }
                g_colorWavePositions[i] = 0;
            }
        }
    }
    else
    {
        for (byte i = 0; i < g_colorWavePositionCount; i++)
        {
            g_colorWavePositions[i]--;
            if (g_colorWavePositions[i] >= g_colorWaveInfo.Size)
            {
                g_colorWavePositions[i] = g_colorWaveInfo.Size - 1;
                if (i == g_colorWavePositionCount - 1)
                {
                    cycleComplete = true;
                }
            }
        }
    }

    // Increment the light count and handle wait signaling as needed.
    if (count_ < g35_.get_light_count())
    {
        ++count_;
    }
    else
    {
        if (cycleComplete && IS_WAIT(option_))
        {
            DebugPrintf("Waiting...\n");
            waiting_ = true;
        }
    }
    
    return delay_;
}

void Wave::Update(pattern_t pattern, option_t option, delay_t delay)
{
    DebugPrintf("Updating...\n");
    Initialize(pattern, option, delay);
}


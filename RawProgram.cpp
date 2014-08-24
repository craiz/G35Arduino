
#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_RAW
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <RawProgram.h>
#include <ColorNodeUtils.h>
#include <ColorUtils.h>

RawProgram::RawProgram(G35& g35, RawCommand *pCommand)
  : LightProgram(g35),
    m_loopCounter(0),
    m_pCommand(pCommand)
{
    DebugPrintf("RawProgram\n");

    m_lightCount = (m_pCommand->end_bulb - m_pCommand->start_bulb) + 1;

    DebugPrintf("  Start: %u\n", m_pCommand->start_bulb);
    DebugPrintf("  End: %u\n", m_pCommand->end_bulb);
    DebugPrintf("  Intensity: %u\n", m_pCommand->intensity);
    DebugPrintf("  Bulb Delay: %u\n", m_pCommand->bulb_delay);
    DebugPrintf("  Light Count: %u\n", m_lightCount);
}

uint32_t RawProgram::Do()
{
    if (m_loopCounter >= m_lightCount)
    {
        m_loopCounter = 0;
    }

    byte *pRawColors = ((byte *)m_pCommand) + sizeof(RawCommand);
    
    DebugPrintf("Bulb: %u Color: %u\n", m_pCommand->start_bulb + m_loopCounter, pRawColors[m_loopCounter]);

    COLOR_INFO colorInfo;
    DecodeColorInfo(pRawColors[m_loopCounter], &colorInfo);
    color_t color = GetPaleteColor(&colorInfo);
    g35_.set_color(m_pCommand->start_bulb + m_loopCounter, m_pCommand->intensity, color);

    m_loopCounter++;
    return m_pCommand->bulb_delay;
}



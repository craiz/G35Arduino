

#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_STROBE_FILL
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <StrobeFill.h>
#include <ColorNodeCommands.h>


StrobeFill::StrobeFill(G35& g35, ProgramCommand *pCommand)
  : LightProgram(g35)
  , m_pCommand(pCommand)
  , m_Stage(0)
{
    DebugPrintf("StrobeFill\n");
}

bool StrobeFill::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    DebugPrintf("Initializing...\n");

    LightProgram::Initialize(pattern, option, delay);

    // Setup default pattern as delay default.
    // This allows different length strings to adjust their
    // strobe wait so they fill the string at the same time.
    pattern_ = pattern;
    if (pattern_ == DELAY_DEFAULT)
    {
        pattern_ = delay_default_;
    }

    // Get colors if available.
    if (m_pCommand)
    {
        uint8_t * extraData = (uint8_t *)m_pCommand + sizeof(ProgramCommand);
        color_t * colors = (color_t *)&extraData[0];

        m_BackgroundColor = colors[0];
        m_FillColor = colors[1];
        m_StrobeColor = colors[2];
    }
    else
    {
        m_BackgroundColor = COLOR_BLACK;
        m_FillColor = COLOR_BLUE;
        m_StrobeColor = COLOR_WHITE;
    }

    m_StrobeWait = pattern_;


#if DEBUG_ENABLED
    uint8_t r, g, b;
    color_t color;
    color = m_BackgroundColor;
    r = color & 0x0F;
    g = (color >> 4) & 0x0F;
    b = (color >> 8) & 0x0F;
    DebugPrintf("Background Color: %d,%d,%d\n", r, g, b);

    color = m_FillColor;
    r = color & 0x0F;
    g = (color >> 4) & 0x0F;
    b = (color >> 8) & 0x0F;
    DebugPrintf("Fill Color: %d,%d,%d\n", r, g, b);

    color = m_StrobeColor;
    r = color & 0x0F;
    g = (color >> 4) & 0x0F;
    b = (color >> 8) & 0x0F;
    DebugPrintf("Strobe Color: %d,%d,%d\n", r, g, b);

    DebugPrintf("Delay: %u\n", delay_);
    DebugPrintf("StrobeWait: %u\n", m_StrobeWait);
#endif

    if (IS_FORWARD(option_))
    {
        m_CurrentBulb = 0;
        m_TargetBulb = light_count_ - 1;
        m_Increment = 1;
    }
    else
    {
        m_CurrentBulb = light_count_ - 1;
        m_TargetBulb = 0;
        m_Increment = -1;
    }

    if (IS_FILL_IMMEDIATE(option_))
    {
        DebugPrintf("Immediate fill background\n");
        g35_.fill_color(0, light_count_, G35::MAX_INTENSITY, m_BackgroundColor);
    }

    return true;
}

uint32_t StrobeFill::Do()
{
    delay_t currentDelay;

    DebugPrintf("Current Stage=%u\n", m_Stage);

    switch (m_Stage)
    {
    case 0: // Strobe Color On
        g35_.set_color(m_CurrentBulb, G35::MAX_INTENSITY, m_StrobeColor);
        currentDelay = m_StrobeWait;
        m_Stage++;
        break;

    case 1: // Strobe Color Off
        if (m_StrobeWait)
        {
            g35_.set_color(m_CurrentBulb, G35::MAX_INTENSITY, m_FillColor);
        }
        currentDelay = delay_;
        m_Stage++;
        break;

    case 2: // Set Fill Color
    // TODO: PAUL: Don't set color here if there is a strobe wait.
        g35_.set_color(m_CurrentBulb, G35::MAX_INTENSITY, m_FillColor);
        currentDelay = 0;
        m_Stage++;
        break;

    case 3: // Advance Current Bulb

        // Check if done and increment to next bulb.
        if (m_CurrentBulb == m_TargetBulb)
        {
            m_Stage = 4;
        }
        else
        {
            m_CurrentBulb += m_Increment;
            m_Stage = 0;
        }
        currentDelay = 0;
        break;

    case 4: // Done
        break;
    }

    return currentDelay;
}

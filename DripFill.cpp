

#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_DRIP_FILL
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <DripFill.h>
#include <ColorUtils.h>

DripFill::DripFill(G35& g35, ProgramCommand *pCommand)
  : LightProgram(g35)
  , m_pCommand(pCommand)
  , m_FillSize(1)
  , m_DripSize(1)
  , m_FillMode(FILL_MODE_ONE_DIRECTION)
  , m_WaitMode(WAIT_MODE_PER_CYCLE)
{
    DebugPrintf("DripFill\n");

    m_TargetBulb = light_count_ - 1;
}

bool DripFill::Initialize(pattern_t pattern, uint8_t option, delay_t delay)
{
    DebugPrintf("Initializing...\n");

    LightProgram::Initialize(pattern, option, delay);

    if (option_ & OPTION_BIT_5)
    {
        m_FillMode = FILL_MODE_BOTH_DIRECTIONS;
    }
    if (option_ & OPTION_BIT_6)
    {
        m_WaitMode = WAIT_MODE_PER_ITEM;
    }

    // Get extra options if available.
    if (m_pCommand)
    {
        uint8_t *pExtraOptions = (uint8_t *)m_pCommand + sizeof(ProgramCommand);
        DecodeColorInfo(pExtraOptions[0], &m_BackgroundColorInfo);
        DecodeColorInfo(pExtraOptions[1], &m_FillColorInfo);
        DecodeColorInfo(pExtraOptions[2], &m_DripColorInfo);
        m_DripSize = pExtraOptions[3];
        m_FillSize = pExtraOptions[4];
    }
    if (m_DripSize == 0)
    {
        m_DripSize = 1;
    }
    if (m_FillSize == 0)
    {
        m_FillSize = 1;
    }

    // Pick random color if requested.
    if (IS_RANDOM(option_))
    {
        m_BackgroundColorInfo.index = GetRandomPaleteColor(m_BackgroundColorInfo.palete, NO_EXCLUDE, NO_EXCLUDE);
        m_FillColorInfo.index = GetRandomPaleteColor(m_FillColorInfo.palete, m_BackgroundColorInfo.index, NO_EXCLUDE);
        m_DripColorInfo.index = GetRandomPaleteColor(m_DripColorInfo.palete, m_BackgroundColorInfo.index, NO_EXCLUDE);
    }

    // Translate COLOR_INFO into RGB color values.
    TranslateColors();

    // If fill immediate, then paint the background color.
    // Otherwise it will be painted as the first drip falls.
    if (IS_FILL_IMMEDIATE(option_))
    {
        g35_.fill_color(0, light_count_, G35::MAX_INTENSITY, m_BackgroundColor);
    }

    m_Forward = IS_FORWARD(option_);
    if (m_Forward)
    {
        m_Bulb = 0;
        m_TargetBulb = light_count_ - m_FillSize;
    }
    else
    {
        m_Bulb = light_count_ - 1;
        m_TargetBulb = m_FillSize;
    }
    m_DoneBulb = m_Bulb;


    return true;
}

void DripFill::TranslateColors()
{
    // Convert to real colors
    m_BackgroundColor = GetPaleteColor(&m_BackgroundColorInfo);
    m_FillColor = GetPaleteColor(&m_FillColorInfo);

    // Set the drip color
    switch(pattern_)
    {
    default:
    case 0: // Drip is same as fill color
        m_DripColor = m_FillColor;
        break;
    case 1: // Drip is white
        m_DripColor = COLOR_WHITE;
        break;
    case 2: // Drip is black
        m_DripColor = COLOR_BLACK;
        break;
    case 3: // Drip is an independent color
        m_DripColor = GetPaleteColor(&m_DripColorInfo);
        break;
    }
}

uint32_t DripFill::Do()
{
    // Clear previous drip position
    if (m_Bulb > (m_DripSize - 1) && m_Forward)
    {
        for (int i = 0; i < m_DripSize; i++)
        {
            g35_.set_color(m_Bulb - m_DripSize + i, G35::MAX_INTENSITY, m_BackgroundColor);
        }
    }
    else if (m_Bulb < (light_count_ - m_DripSize) && !m_Forward)
    {
        for (int i = 0; i < m_DripSize; i++)
        {
            g35_.set_color(m_Bulb + m_DripSize - i, G35::MAX_INTENSITY, m_BackgroundColor);
        }
    }

    // Draw current drip position
    if (m_Forward)
    {
        for (int i = 0; i < m_DripSize; i++)
        {
            g35_.set_color(m_Bulb + i, G35::MAX_INTENSITY, m_DripColor);
        }
    }
    else
    {
        for (int i = 0; i < m_DripSize; i++)
        {
            g35_.set_color(m_Bulb - i, G35::MAX_INTENSITY, m_DripColor);
        }
    }

    // update next drip position
    if (m_Bulb == m_TargetBulb)
    {
        if (m_Forward)
        {
            for (uint8_t i = 0; i < m_FillSize; i++)
            {
                g35_.set_color(m_Bulb + i, G35::MAX_INTENSITY, m_FillColor);
            }
        }
        else
        {
            for (uint8_t i = 0; i < m_FillSize; i++)
            {
                g35_.set_color(m_Bulb - i, G35::MAX_INTENSITY, m_FillColor);
            }
        }

        // Check if all filled up.
        if (m_TargetBulb == m_DoneBulb)
        {
            // Update colors
            COLOR_INFO tempColorInfo = m_BackgroundColorInfo;
            m_BackgroundColorInfo = m_FillColorInfo;
            if (IS_RANDOM(option_))
            {
                // Pick new random fill color
                m_FillColorInfo.index = GetRandomPaleteColor(m_FillColorInfo.palete, m_BackgroundColorInfo.index, NO_EXCLUDE);
                m_DripColorInfo.index = GetRandomPaleteColor(m_DripColorInfo.palete, m_BackgroundColorInfo.index, NO_EXCLUDE);
            }
            else
            {
                // Fill color is old background color
                m_FillColorInfo = tempColorInfo;
            }

            // Translate COLOR_INFO into RGB color values.
            TranslateColors();

            // Reset current and target bulbs
            if (m_FillMode == FILL_MODE_BOTH_DIRECTIONS)
            {
                m_Forward = !m_Forward;
            }
            if (m_Forward)
            {
                m_TargetBulb = light_count_ - m_FillSize;
                m_Bulb = 0;
            }
            else
            {
                m_TargetBulb = m_FillSize - 1;
                m_Bulb = light_count_ - 1;
            }
            m_DoneBulb = m_Bulb;

            // Always wait when drip cycle is complete.
            if (IS_WAIT(option_))
            {
                DebugPrintf("Waiting...\n");
                waiting_ = true;
            }
        }
        else
        {
            // Setup for next drip
            if (m_Forward)
            {
                if (m_TargetBulb >= m_FillSize)
                {
                    m_TargetBulb -= m_FillSize;
                }
                else
                {
                    m_TargetBulb = 0;
                }
                m_Bulb = 0;
            }
            else
            {
                if (m_TargetBulb + m_FillSize < light_count_)
                {
                    m_TargetBulb += m_FillSize;
                }
                else
                {
                    m_TargetBulb = light_count_ - 1;
                }
                m_Bulb = light_count_ - 1;
            }

            // Only wait if configured to wait after each drop.
            if (IS_WAIT(option_) && m_WaitMode == WAIT_MODE_PER_ITEM)
            {
                DebugPrintf("Waiting...\n");
                waiting_ = true;
            }
        }
    }
    else
    {
        // Move the drip
        light_count_t moveSize = m_DripSize;
        if (m_Forward && (m_TargetBulb - m_Bulb < m_DripSize))
        {
            moveSize = m_TargetBulb - m_Bulb;
        }
        else if (!m_Forward && (m_Bulb - m_TargetBulb < m_DripSize))
        {
            moveSize = m_Bulb - m_TargetBulb;
        }

        if (m_Forward)
        {
            m_Bulb += moveSize;
        }
        else
        {
            m_Bulb -= moveSize;
        }
    }

    return delay_;
}



#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_SOLID
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <Solid.h>
#include <RainbowUtils.h>
#include <ColorUtils.h>

Solid::Solid(G35& g35)
  : SingleColorProgram(g35),
    m_Intensity(0)
{
    DebugPrintf("Solid\n");
}

bool Solid::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    DebugPrintf("Initializing...\n");

    SingleColorProgram::Initialize(pattern, option, delay);

    Reset();

    return true;
}

void Solid::Update(pattern_t pattern, option_t option, delay_t delay)
{
    DebugPrintf("Updating...\n");

    Initialize(pattern, option, delay);
}

void Solid::Kick(void)
{
    SetupColor(true);
    Reset();
}

void Solid::Reset()
{
    if (IS_FILL_IMMEDIATE(option_) || !IS_FORWARD(option_))
    {
        m_Intensity = G35::MAX_INTENSITY;
    }
    else if (IS_FORWARD(option_))
    {
        m_Intensity = 0;
    }

    g35_.fill_color(0, light_count_, m_Intensity, m_color);
    m_Done = false;
}

uint32_t Solid::Do()
{
    if (!IS_FILL_IMMEDIATE(option_) && !m_Done)
    {
        if (IS_FORWARD(option_) && (m_Intensity <= G35::MAX_INTENSITY))
        {
            m_Intensity++;
        }
        else if (!IS_FORWARD(option_) && (m_Intensity > 0))
        {
            m_Intensity--;
        }
        else
        {
            m_Done = true;
        }
        g35_.broadcast_intensity(m_Intensity);
    }

    return delay_;
}


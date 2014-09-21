#include <DebugConfig.h>
#if DEBUG_G35
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <G35StringSimulator.h>

G35StringSimulator::G35StringSimulator()
: G35StringWindowSmall()
{
}

void G35StringSimulator::Configure(uint8_t pin, light_count_t light_count,
                     light_count_t physical_light_count,
                     light_count_t bulb_zero, bool is_forward,
                     STRING_LAYOUT layout)
{
    G35String::Configure(pin, light_count, physical_light_count, bulb_zero, is_forward, layout);

    m_colors = new color_t[physical_light_count];
    memset(m_colors, 0, sizeof(color_t) * physical_light_count);
}


light_count_t G35StringSimulator::get_light_count()
{
    return light_count_;
}

void G35StringSimulator::set_color(light_count_t bulb, uint8_t intensity, color_t color)
{
    color_t color2 = 0;

    for (int i = 0; i < 3; i++)
    {
        color2 = color2 << 4;
        color2 = color2 | (color & 0xf);
        color = color >> 4;
    }
    
    m_colors[bulb] = color2;
}

color_t G35StringSimulator::get_color(light_count_t bulb)
{
    return m_colors[bulb];
}


/*
 This program creates spinning/twinkling effect for a light string configured in the shape of a 6 armed snowflake.

  By Paul Irwin
*/

#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_SNOWFLAKE
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <Snowflake.h>
#include <avr/pgmspace.h>


#define SNOWFLAKE_ARM_MAP_LENGTH 31
PROGMEM prog_uchar snowflake_arm_map[SNOWFLAKE_ARM_MAP_LENGTH] =  { 
     0,
     1,  3,  4,  7, 10,
    11, 13, 14, 17, 20,
    21, 23, 24, 27, 30,
    31, 33, 34, 37, 40,
    41, 43, 44, 47, 50,
    51, 53, 54, 57, 60,
    };

#define SNOWFLAKE_TIP_MAP_LENGTH 30
PROGMEM prog_uchar snowflake_tip_map[SNOWFLAKE_TIP_MAP_LENGTH] =  { 
     2,  5,  6,  8,  9,
    12, 15, 16, 18, 19,
    22, 25, 26, 28, 29,
    32, 35, 36, 38, 39,
    42, 45, 46, 48, 49,
    52, 55, 56, 58, 59,
    };


G35SnowflakeBigSection::G35SnowflakeBigSection(G35& g35, SNOWFLAKE_SECTION section)
    : G35()
    , m_g35(g35)
    , m_section(section)
{
    switch (m_section)
    {
        case SNOWFLAKE_SECTION_ARMS:
            light_count_ = SNOWFLAKE_ARM_MAP_LENGTH;
            break;

        case SNOWFLAKE_SECTION_TIPS:
            light_count_ = SNOWFLAKE_TIP_MAP_LENGTH;
            break;
    }
}

light_count_t G35SnowflakeBigSection::get_light_count()
{
    return light_count_;
}

void G35SnowflakeBigSection::set_light_count(light_count_t light_count)
{
    // Do nothing.
}

void G35SnowflakeBigSection::set_color(light_count_t bulb, uint8_t intensity, color_t color)
{
    light_count_t physical_bulb;
    switch (m_section)
    {
    case SNOWFLAKE_SECTION_ARMS:
        physical_bulb = pgm_read_byte(&(snowflake_arm_map[bulb]));
        break;

    case SNOWFLAKE_SECTION_TIPS:
        physical_bulb = pgm_read_byte(&(snowflake_tip_map[bulb]));
        break;
    }

    m_g35.set_color(physical_bulb, intensity, color);
}

light_count_t G35SnowflakeBigSection::get_broadcast_bulb()
{
    return m_g35.get_broadcast_bulb();
}



Snowflake::Snowflake(G35& g35)
  : LightProgram(g35)
  , m_Arms(g35, SNOWFLAKE_SECTION_ARMS)
  , m_Tips(g35, SNOWFLAKE_SECTION_TIPS)
{
    DebugPrintf("Snowflake\n");
}

Snowflake::~Snowflake()
{
    Uninitialize();
}

void Snowflake::Uninitialize()
{
}

bool Snowflake::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    DebugPrintf("Initializing...\n");
    LightProgram::Initialize(pattern, option, delay);

    return true;
}

uint32_t Snowflake::Do()
{
    return delay_;
}


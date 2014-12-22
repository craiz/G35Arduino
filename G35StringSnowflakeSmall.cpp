
#include <DebugConfig.h>
#if DEBUG_G35
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <G35StringSnowflakeSmall.h>
#include <avr/pgmspace.h>

#define XX 0xFF

// Snowflake small mapping

#define SNOWFLAKE_SMALL_RING_COUNT 7
#define SNOWFLAKE_SMALL_RING_LENGTH 12
PROGMEM prog_uchar snowflake_small_rings[SNOWFLAKE_SMALL_RING_COUNT][SNOWFLAKE_SMALL_RING_LENGTH] = {
    { 0, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 1,  9, 17, 25, 33, 41, XX, XX, XX, XX, XX, XX },
    { 2, 10, 18, 26, 34, 42, XX, XX, XX, XX, XX, XX },
    { 3, 11, 19, 27, 35, 43, XX, XX, XX, XX, XX, XX },
    { 4,  8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48 },
    { 6, 14, 22, 30, 38, 46, XX, XX, XX, XX, XX, XX },
    { 5,  7, 13, 15, 21, 23, 29, 31, 37, 39, 45, 47 },
    };

#define SNOWFLAKE_SMALL_BLADE_COUNT 6
#define SNOWFLAKE_SMALL_BLADE_LENGTH 8
PROGMEM prog_uchar snowflake_small_blades[SNOWFLAKE_SMALL_BLADE_COUNT] =  { 1, 9, 17, 25, 33, 41 };


// TODO: Finish horizontal line mapping
#if 0
#define SNOWFLAKE_SMALL_LINE_COUNT 16
#define SNOWFLAKE_SMALL_LINE_LENGTH 12
PROGMEM prog_uchar lines[SNOWFLAKE_LINE_COUNT][SNOWFLAKE_LINE_LENGTH] = {
    {  0, XX, XX, XX, XX, XX, XX, XX, XX, XX, 40, XX }
    { XX,  1, 48, 49, XX, XX, XX, 42, 41, 39, XX, XX },
    { XX, XX,  2, XX, 47, XX, 43, XX, 38, XX, XX, XX },
    { XX, XX, XX,  3, 46, 45, 44, 37, XX, XX, XX, XX },
    { XX, XX, XX, XX,  4, XX, 36, XX, XX, XX, XX, XX },
    { XX, XX, XX, XX, XX,  5, 35, XX, XX, XX, XX, XX },
    { XX, XX, XX, XX,  6, XX, 34, XX, XX, XX, XX, XX },
    { XX, XX, XX,  7, XX, XX, XX, 33, XX, XX, XX, XX },
    { XX, XX,  8, XX, XX, XX, XX, XX, 32, XX, XX, XX },
    { XX,  9, XX, XX, XX, XX, XX, XX, XX, 31, XX, XX },
    { 10, 11, 12, 13, 14, 15, 25, 26, 27, 28, 29, 30 },
    { XX, 16, XX, XX, XX, XX, XX, XX, XX, 24, XX, XX },
    { XX, XX, 17, XX, XX, XX, XX, XX, 23, XX, XX, XX },
    { XX, XX, XX, 18, XX, XX, XX, 22, XX, XX, XX, XX },
    { XX, XX, XX, XX, 19, XX, 21, XX, XX, XX, XX, XX },
    { XX, XX, XX, XX, XX, 20, XX, XX, XX, XX, XX, XX },
    };
#endif


G35StringSnowflakeSmall::G35StringSnowflakeSmall()
: G35String()
{
    DebugPrintf("G35StringSnowflakeSmall\n");
}

light_count_t G35StringSnowflakeSmall::get_light_count()
{
    switch (layout_)
    {
    case STRING_LAYOUT_RINGS_CENTER:
    case STRING_LAYOUT_RINGS_CORNER:
    case STRING_LAYOUT_SNOWFLAKE_RINGS:    return SNOWFLAKE_SMALL_RING_COUNT;

    case STRING_LAYOUT_SIDES:
    case STRING_LAYOUT_SNOWFLAKE_BLADES:   return SNOWFLAKE_SMALL_BLADE_COUNT;
    }

    // Any other mode is treated as a linear string with a 1:1 mapping
    // between physical and virtual bulbs.
    return light_count_;
}

void G35StringSnowflakeSmall::set_layout(STRING_LAYOUT layout)
{
    layout_ = layout;

    // For blade mode, the center bulb is not used.
    if (layout_ == STRING_LAYOUT_SNOWFLAKE_BLADES)
    {
        G35String::set_color(0, 0, COLOR_BLACK);
    }
}

void G35StringSnowflakeSmall::set_color(light_count_t bulb, uint8_t intensity, color_t color)
{
    byte bulb_map_size;
    light_count_t *bulb_mapping = NULL;
    light_count_t physical_bulb;

    switch (layout_)
    {
// TODO:
#if 0

    case STRING_LAYOUT_SNOWFLAKE_LINEAR_CLOCKWISE:
        bulb_mapping = snowflake_linear_clockwise;
        break;

    // To match the behavior of the big snowflake, the small snowflake linear is counter clockwise.
    case STRING_LAYOUT_LINEAR:
    case STRING_LAYOUT_SNOWFLAKE_LINEAR_COUNTERCLOCKWISE:
        break;
#endif

    case STRING_LAYOUT_SIDES:
    case STRING_LAYOUT_SNOWFLAKE_BLADES:
        bulb_map_size = SNOWFLAKE_SMALL_BLADE_LENGTH;
        bulb_mapping = snowflake_small_blades;
        break;

    // TODO: Rings
    }

    switch (layout_)
    {
    default:
    case STRING_LAYOUT_LINEAR:
    case STRING_LAYOUT_SNOWFLAKE_LINEAR_COUNTERCLOCKWISE:
        G35String::set_color(bulb, intensity, color);
        break;

    case STRING_LAYOUT_SNOWFLAKE_LINEAR_CLOCKWISE:
        physical_bulb = pgm_read_byte(&(bulb_mapping[bulb]));
        G35String::set_color(physical_bulb, intensity, color);
        break;

// TODO:
#if 0
    case STRING_LAYOUT_RINGS_CENTER:
    case STRING_LAYOUT_RINGS_CORNER:
    case STRING_LAYOUT_SNOWFLAKE_RINGS:
        for (byte i = 0; i < SNOWFLAKE_RING_LENGTH; i++)
        {
            physical_bulb = bulb + (i * SNOWFLAKE_RING_INTERVAL);

            DebugPrintf("Setting Bulb: %u\n", physical_bulb);
            G35String::set_color(physical_bulb, intensity, color);

            // Special case for ring 0
            if (bulb == 0)
            {
                break;
            }
        }
        break;
#endif

    case STRING_LAYOUT_SIDES:
    case STRING_LAYOUT_SNOWFLAKE_BLADES:
        for (byte i = 0; i < bulb_map_size; i++)
        {
            physical_bulb = pgm_read_byte(&(bulb_mapping[bulb])) + i;

            DebugPrintf("Setting Bulb: %u\n", physical_bulb);
            G35String::set_color(physical_bulb, intensity, color);
        }
        break;

    case STRING_LAYOUT_SNOWFLAKE_REDUCED:
        for (byte i = 0; i < bulb_map_size; i++)
        {
            physical_bulb = pgm_read_byte(&(bulb_mapping[i]));
            if (physical_bulb == XX)
            {
                continue;
            }
            DebugPrintf("Setting Bulb: %u\n", physical_bulb);
            G35String::set_color(physical_bulb, intensity, color);
        }
    }
}


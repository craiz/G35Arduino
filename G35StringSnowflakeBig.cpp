
#include <DebugConfig.h>
#if DEBUG_G35
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <G35StringSnowflakeBig.h>
#include <avr/pgmspace.h>

#define XX 0xFF

#define SNOWFLAKE_BIG_LINEAR_COUNTERCLOCKWISE_COUNT 61
PROGMEM prog_uchar snowflake_big_linear_counterclockwise[SNOWFLAKE_BIG_LINEAR_COUNTERCLOCKWISE_COUNT] = 
    {  0,
       1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
      51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
      41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
      31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
      21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
      11, 12, 13, 14, 15, 16, 17, 18, 19, 20
    };


// Snowflake rings radiating from center out to tips.
// Each ring consists of 1 bulb from each blade.  This means we do 
// not need to store the mapping and can just calculate virtual:physical mapping directly
// based on bulb number.
#define SNOWFLAKE_BIG_RING_COUNT 11
#define SNOWFLAKE_BIG_RING_LENGTH 6
#define SNOWFLAKE_BIG_RING_INTERVAL 10


#define SNOWFLAKE_BIG_BLADE_COUNT 6
#define SNOWFLAKE_BIG_BLADE_LENGTH 10
PROGMEM prog_uchar snowflake_big_blades[SNOWFLAKE_BIG_BLADE_COUNT] =  { 1, 11, 21, 31, 41, 51 };


// 49 bulb version of snowflake
#define SNOWFLAKE_BIG_REDUCED_MAP_COUNT 49
#define SNOWFLAKE_BIG_REDUCED_MAP_LENGTH 2
PROGMEM prog_uchar snowflake_big_reduced[SNOWFLAKE_BIG_REDUCED_MAP_COUNT][SNOWFLAKE_BIG_REDUCED_MAP_LENGTH] = {
    {  0, XX }, // 0

    {  1, XX }, // 1
    {  2, XX }, // 2
    {  3, XX }, // 3
    {  4, XX }, // 4
    {  5,  7 }, // 5
    {  6, XX }, // 6
    {  8, 10 }, // 7
    {  9, XX }, // 8

    { 11, XX }, // 9
    { 12, XX }, // 10
    { 13, XX }, // 11
    { 14, XX }, // 12
    { 15, 17 }, // 13
    { 16, XX }, // 14
    { 18, 20 }, // 15
    { 19, XX }, // 16

    { 21, XX }, // 17
    { 22, XX }, // 18
    { 23, XX }, // 19
    { 24, XX }, // 20
    { 25, 27 }, // 21
    { 26, XX }, // 22
    { 28, 30 }, // 23
    { 29, XX }, // 24

    { 31, XX }, // 25
    { 32, XX }, // 26
    { 33, XX }, // 27
    { 34, XX }, // 28
    { 35, 37 }, // 29
    { 36, XX }, // 30
    { 38, 40 }, // 31
    { 39, XX }, // 32

    { 41, XX }, // 33
    { 42, XX }, // 34
    { 43, XX }, // 35
    { 44, XX }, // 36
    { 45, 47 }, // 37
    { 46, XX }, // 38
    { 48, 50 }, // 39
    { 49, XX }, // 40
 
    { 51, XX }, // 41
    { 52, XX }, // 42
    { 53, XX }, // 43
    { 54, XX }, // 44
    { 55, 57 }, // 45
    { 56, XX }, // 46
    { 58, 60 }, // 47
    { 59, XX }, // 48
    };



#define SNOWFLAKE_BIG_LINE_COUNT 41
#define SNOWFLAKE_BIG_LINE_LENGTH 2
PROGMEM prog_uchar snowflake_big_lines[SNOWFLAKE_BIG_LINE_COUNT][SNOWFLAKE_BIG_LINE_LENGTH] = {
    { 10, XX },
    {  9, XX },
    {  8, XX },
    {  7, XX },
    {  6, XX },
    {  5, XX },
    {  4, XX },
    {  3, XX },
    {  2, XX },
    {  1, XX },

    {  0, XX },

    { 11, 51 },
    { 12, 52 },
    { 13, 53 },
    { 14, 54 },
    { 15, 55 },
    { 16, 56 },
    { 17, 57 },
    { 18, 58 },
    { 19, 59 },
    { 20, 60 },

    { 21, 41 },
    { 22, 42 },
    { 23, 43 },
    { 24, 44 },
    { 25, 45 },
    { 26, 46 },
    { 27, 47 },
    { 28, 48 },
    { 29, 49 },
    { 30, 50 },

    { 31, XX },
    { 32, XX },
    { 33, XX },
    { 34, XX },
    { 35, XX },
    { 36, XX },
    { 37, XX },
    { 38, XX },
    { 39, XX },
    { 40, XX },
    };


#define SNOWFLAKE_BIG_LINE_CENTER_COUNT 21
#define SNOWFLAKE_BIG_LINE_CENTER_LENGTH 4
PROGMEM prog_uchar snowflake_big_lines_center[SNOWFLAKE_BIG_LINE_CENTER_COUNT][SNOWFLAKE_BIG_LINE_CENTER_LENGTH] = {
    {  0, XX, XX, XX },

    { 11, 21, 41, 51 },
    { 12, 22, 42, 52 },
    { 13, 23, 43, 53 },
    { 14, 24, 44, 54 },
    { 15, 25, 45, 55 },
    { 16, 26, 46, 56 },
    { 17, 27, 47, 57 },
    { 18, 28, 48, 58 },
    { 19, 29, 49, 59 },
    { 20, 30, 50, 60 },

    {  1, 31, XX, XX },
    {  2, 32, XX, XX },
    {  3, 33, XX, XX },
    {  4, 34, XX, XX },
    {  5, 35, XX, XX },
    {  6, 36, XX, XX },
    {  7, 37, XX, XX },
    {  8, 38, XX, XX },
    {  9, 39, XX, XX },
    { 10, 40, XX, XX },
    };


G35StringSnowflakeBig::G35StringSnowflakeBig()
: G35String()
{
    DebugPrintf("G35StringSnowflakeBig\n");
}

light_count_t G35StringSnowflakeBig::get_light_count()
{
    switch (layout_)
    {
    case STRING_LAYOUT_RINGS_CENTER:
    case STRING_LAYOUT_RINGS_CORNER:
    case STRING_LAYOUT_SNOWFLAKE_RINGS:    return SNOWFLAKE_BIG_RING_COUNT;

    case STRING_LAYOUT_SIDES:
    case STRING_LAYOUT_SNOWFLAKE_BLADES:   return SNOWFLAKE_BIG_BLADE_COUNT;

    case STRING_LAYOUT_SNOWFLAKE_REDUCED:  return SNOWFLAKE_BIG_REDUCED_MAP_COUNT;

    case STRING_LAYOUT_HORIZONTAL_LINES:
    case STRING_LAYOUT_SNOWFLAKE_LINES:    return SNOWFLAKE_BIG_LINE_COUNT;

    case STRING_LAYOUT_HORIZONTAL_LINES_CENTER: return SNOWFLAKE_BIG_LINE_CENTER_COUNT;
    }

    // Any other mode is treated as a linear string with a 1:1 mapping
    // between physical and virtual bulbs.
    return light_count_;
}

void G35StringSnowflakeBig::set_layout(STRING_LAYOUT layout)
{
    layout_ = layout;

    // For blade mode, the center bulb is not used.
    if (layout_ == STRING_LAYOUT_SNOWFLAKE_BLADES)
    {
        G35String::set_color(0, 0, COLOR_BLACK);
    }
}

// TODO: Need all string layouts to handle broadcast bulb.
void G35StringSnowflakeBig::set_color(light_count_t bulb, uint8_t intensity, color_t color)
{
    byte bulb_map_size;
    light_count_t *bulb_mapping = NULL;
    light_count_t physical_bulb;

    switch (layout_)
    {
    case STRING_LAYOUT_SNOWFLAKE_LINEAR_CLOCKWISE:
        bulb_mapping = snowflake_big_linear_counterclockwise;
        break;
    
    case STRING_LAYOUT_SIDES:
    case STRING_LAYOUT_SNOWFLAKE_BLADES:
        bulb_map_size = SNOWFLAKE_BIG_BLADE_LENGTH;
        bulb_mapping = snowflake_big_blades;
        break;

    case STRING_LAYOUT_HORIZONTAL_LINES:
    case STRING_LAYOUT_SNOWFLAKE_LINES:
        bulb_map_size = SNOWFLAKE_BIG_LINE_LENGTH;
        bulb_mapping = snowflake_big_lines[bulb];
        break;

    case STRING_LAYOUT_HORIZONTAL_LINES_CENTER:
        bulb_map_size = SNOWFLAKE_BIG_LINE_CENTER_LENGTH;
        bulb_mapping = snowflake_big_lines_center[bulb];
        break;

    case STRING_LAYOUT_SNOWFLAKE_REDUCED:
        bulb_map_size = SNOWFLAKE_BIG_REDUCED_MAP_LENGTH;
        bulb_mapping = snowflake_big_reduced[bulb];
        break;
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

    case STRING_LAYOUT_RINGS_CENTER:
    case STRING_LAYOUT_RINGS_CORNER:
    case STRING_LAYOUT_SNOWFLAKE_RINGS:
        for (byte i = 0; i < SNOWFLAKE_BIG_RING_LENGTH; i++)
        {
            physical_bulb = bulb + (i * SNOWFLAKE_BIG_RING_INTERVAL);

            DebugPrintf("Setting Bulb: %u\n", physical_bulb);
            G35String::set_color(physical_bulb, intensity, color);

            // Special case for ring 0
            if (bulb == 0)
            {
                break;
            }
        }
        break;

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
    case STRING_LAYOUT_HORIZONTAL_LINES:
    case STRING_LAYOUT_SNOWFLAKE_LINES:
    case STRING_LAYOUT_HORIZONTAL_LINES_CENTER:
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
        break;
    }
}


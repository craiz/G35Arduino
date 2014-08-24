
#include <DebugConfig.h>
#if DEBUG_G35
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <G35StringStar.h>
#include <avr/pgmspace.h>

#define XX 0xFF

#define RING_COUNT 6
#define RING_LENGTH 10
PROGMEM prog_uchar rings[RING_COUNT][RING_LENGTH] = {
    { 5, 15, 25, 35, 45, XX, XX, XX, XX, XX },
    { 4,  6, 14, 16, 24, 26, 34, 36, 44, 46 },
    { 3,  7, 13, 17, 23, 27, 33, 37, 43, 47 },
    { 2,  8, 12, 18, 22, 28, 32, 38, 42, 48 },
    { 1,  9, 11, 19, 21, 29, 31, 39, 41, 49 },
    { 0, 10, 20, 30, 40, XX, XX, XX, XX, XX }
    };

#define BLADE_COUNT 5
#define BLADE_LENGTH 10
PROGMEM prog_uchar blades[BLADE_COUNT][BLADE_LENGTH] = {
    { 45, 46, 47, 48, 49,  0,  1,  2,  3,  4 },
    {  5,  6,  7,  8,  9, 10, 11, 12, 13, 14 },
    { 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 },
    { 25, 26, 27, 28, 29, 30, 31, 32, 33, 34 },
    { 35, 36, 37, 38, 39, 40, 41, 42, 43, 44 }
    };

#define WING_COUNT 5
#define WING_LENGTH 10
PROGMEM prog_uchar wings[WING_COUNT] =  { 0, 10, 20, 30, 40 };

#define SIDE_COUNT 10
#define SIDE_LENGTH 5
PROGMEM prog_uchar sides[SIDE_COUNT] = { 0, 5, 10, 15, 20, 25, 30, 35, 40, 45 };


// TODO: PAUL: Fix Star horizontal lines to be bottom up like all other strings layouts

#define LINE_COUNT 16
#define LINE_LENGTH 12
PROGMEM prog_uchar lines[LINE_COUNT][LINE_LENGTH] = {
    { XX, XX, XX, XX, XX, 20, XX, XX, XX, XX, XX, XX },
    { XX, XX, XX, XX, 19, XX, 21, XX, XX, XX, XX, XX },
    { XX, XX, XX, 18, XX, XX, XX, 22, XX, XX, XX, XX },
    { XX, XX, 17, XX, XX, XX, XX, XX, 23, XX, XX, XX },
    { XX, 16, XX, XX, XX, XX, XX, XX, XX, 24, XX, XX },
    { 10, 11, 12, 13, 14, 15, 25, 26, 27, 28, 29, 30 },
    { XX,  9, XX, XX, XX, XX, XX, XX, XX, 31, XX, XX },
    { XX, XX,  8, XX, XX, XX, XX, XX, 32, XX, XX, XX },
    { XX, XX, XX,  7, XX, XX, XX, 33, XX, XX, XX, XX },
    { XX, XX, XX, XX,  6, XX, 34, XX, XX, XX, XX, XX },
    { XX, XX, XX, XX, XX,  5, 35, XX, XX, XX, XX, XX },
    { XX, XX, XX, XX,  4, XX, 36, XX, XX, XX, XX, XX },
    { XX, XX, XX,  3, 46, 45, 44, 37, XX, XX, XX, XX },
    { XX, XX,  2, XX, 47, XX, 43, XX, 38, XX, XX, XX },
    { XX,  1, 48, 49, XX, XX, XX, 42, 41, 39, XX, XX },
    {  0, XX, XX, XX, XX, XX, XX, XX, XX, XX, 40, XX }
    };


G35StringStar::G35StringStar()
: G35String()
{
    DebugPrintf("G35StringStar\n");
}

light_count_t G35StringStar::get_light_count()
{
    switch (layout_)
    {
    case STRING_LAYOUT_STAR_RINGS:    return RING_COUNT;
    case STRING_LAYOUT_STAR_BLADES:   return BLADE_COUNT;
    case STRING_LAYOUT_STAR_WINGS:    return WING_COUNT;
    case STRING_LAYOUT_STAR_SIDES:    return SIDE_COUNT;
    case STRING_LAYOUT_STAR_LINES:    return LINE_COUNT;
    case STRING_LAYOUT_HORIZONTAL_LINES: return LINE_COUNT;
    }

    // Any other unrecognized layout is treated as a linear string with a 1:1 mapping
    // between physical and virtual bulbs.
    return light_count_;
}

void G35StringStar::set_color(light_count_t bulb, uint8_t intensity, color_t color)
{
    byte bulb_map_size;
    light_count_t *bulb_mapping = NULL;
    light_count_t physical_bulb;
    switch (layout_)
    {
    case STRING_LAYOUT_STAR_RINGS:
        bulb_map_size = RING_LENGTH;
        bulb_mapping = rings[bulb];
        break;

    case STRING_LAYOUT_STAR_BLADES:
        bulb_map_size = BLADE_LENGTH;
        bulb_mapping = blades[bulb];
        break;

    case STRING_LAYOUT_STAR_WINGS:
        bulb_map_size = WING_LENGTH;
        bulb_mapping = wings;
        break;

    case STRING_LAYOUT_STAR_SIDES:
        bulb_map_size = SIDE_LENGTH;
        bulb_mapping = sides;
        break;

    case STRING_LAYOUT_STAR_LINES:
    case STRING_LAYOUT_HORIZONTAL_LINES:
        bulb_map_size = LINE_LENGTH;
        bulb_mapping = lines[bulb];
        break;
    }

    switch (layout_)
    {
    default:
    case STRING_LAYOUT_LINEAR:
        G35String::set_color(bulb, intensity, color);
        break;

    case STRING_LAYOUT_STAR_RINGS:
    case STRING_LAYOUT_STAR_BLADES:
    case STRING_LAYOUT_STAR_LINES:
    case STRING_LAYOUT_HORIZONTAL_LINES:
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

    case STRING_LAYOUT_STAR_WINGS:
    case STRING_LAYOUT_STAR_SIDES:
        for (byte i = 0; i < bulb_map_size; i++)
        {
            physical_bulb = pgm_read_byte(&(bulb_mapping[bulb])) + i;
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


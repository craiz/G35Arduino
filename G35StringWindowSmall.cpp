
#include <DebugConfig.h>
#if DEBUG_G35
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <G35StringWindowSmall.h>
#include <avr/pgmspace.h>

#define XX 0xFF

//  Window Small Layout
//  Left/Right = 8 bulbs
//  Top/Bottom = 10 bulbs
//
//       1   2   3   4   5   6   7   8   9  10  11  12
//    ------------------------------------------------
//  8 |  7   8   9  10  11  12  13  14  15  16  17  18
//  7 |  6                                          19
//  6 |  5                                          20
//  5 |  4                                          21
//  4 |  3                                          22
//  3 |  2                                          23
//  2 |  1                                          24
//  1 |  0  35  34  33  32  31  30  29  28  27  26  25

// STRING_LAYOUT_SIDES
#define SIDES_COUNT 4
#define SIDES_LENGTH 10
PROGMEM prog_uchar window_small_sides[SIDES_COUNT][SIDES_LENGTH] = {
    {  0,  1,  2,  3,  4,  5,  6,  7, XX, XX },
    {  8,  9, 10, 11, 12, 13, 14, 15, 16, 17 },
    { 18, 19, 20, 21, 22, 23, 24, 25, XX, XX },
    { 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 },
    };

// STRING_LAYOUT_HORIZONTAL_LINES
#define HORIZONTAL_LINES_COUNT 8
#define HORIZONTAL_LINES_LENGTH 12
PROGMEM prog_uchar window_small_horizontal_lines[HORIZONTAL_LINES_COUNT][HORIZONTAL_LINES_LENGTH] = {
    {  0, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25 },
    {  1, 24, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  2, 23, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  3, 22, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  4, 21, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  5, 20, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  6, 19, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18 },
    };

// STRING_LAYOUT_HORIZONTAL_LINES_CENTER
#define HORIZONTAL_LINES_CENTER_COUNT 4
#define HORIZONTAL_LINES_CENTER_LENGTH 24
PROGMEM prog_uchar window_small_horizontal_lines_center[HORIZONTAL_LINES_CENTER_COUNT][HORIZONTAL_LINES_CENTER_LENGTH] = {
    {  3, 22,  4, 21, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  2, 23,  5, 20, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  1, 24,  6, 19, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  0, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18 }
    };

// STRING_LAYOUT_VERTICAL_LINES
#define VERTICAL_LINES_COUNT 12
#define VERTICAL_LINES_LENGTH 8
PROGMEM prog_uchar window_small_vertical_lines[VERTICAL_LINES_COUNT][VERTICAL_LINES_LENGTH] = {
    {  0,  1,  2,  3,  4,  5,  6,  7 },
    { 35,  8, XX, XX, XX, XX, XX, XX },
    { 34,  9, XX, XX, XX, XX, XX, XX },
    { 33, 10, XX, XX, XX, XX, XX, XX },
    { 32, 11, XX, XX, XX, XX, XX, XX },
    { 31, 12, XX, XX, XX, XX, XX, XX },
    { 30, 13, XX, XX, XX, XX, XX, XX },
    { 29, 14, XX, XX, XX, XX, XX, XX },
    { 28, 15, XX, XX, XX, XX, XX, XX },
    { 27, 16, XX, XX, XX, XX, XX, XX },
    { 26, 17, XX, XX, XX, XX, XX, XX },
    { 25, 24, 23, 22, 21, 20, 19, 18 },
    };

// STRING_LAYOUT_VERTICAL_LINES_CENTER
#define VERTICAL_LINES_CENTER_COUNT 6
#define VERTICAL_LINES_CENTER_LENGTH 16
PROGMEM prog_uchar window_small_vertical_lines_center[VERTICAL_LINES_CENTER_COUNT][VERTICAL_LINES_CENTER_LENGTH] = {
    { 31, 12, 30, 13, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 32, 11, 29, 14, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 33, 10, 28, 15, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 34,  9, 27, 16, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 35,  8, 26, 17, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  0,  1,  2,  3,  4,  5,  6,  7, 25, 24, 23, 22, 21, 20, 19, 18 }
    };

// STRING_LAYOUT_RINGS_CENTER
#define RINGS_CENTER_COUNT 9
#define RINGS_CENTER_LENGTH 4
PROGMEM prog_uchar window_small_rings_center[RINGS_CENTER_COUNT][RINGS_CENTER_LENGTH] = {
    { 31, 12, 30, 13 },
    { 32, 11, 29, 14 },
    { 33, 10, 28, 15 },
    { 34,  9, 27, 16 },
    { 35,  8, 26, 17 },
    {  0,  7, 25, 18 },
    {  1,  6, 24, 19 },
    {  2,  5, 23, 20 },
    {  3,  4, 22, 21 },
    };

// STRING_LAYOUT_RINGS_CORNER
#define RINGS_CORNER_COUNT 6
#define RINGS_CORNER_LENGTH 8
PROGMEM prog_uchar window_small_rings_corner[RINGS_CORNER_COUNT][RINGS_CORNER_LENGTH] = {
    {  0,   7, 25, 18, XX, XX, XX, XX },
    {  1,  35,  6,  8, 17, 19, 24, 26 },
    {  2,  34,  5,  9, 16, 20, 23, 27 },
    {  3,  33,  4, 10, 15, 21, 22, 28 },
    {  32, 11, 14, 29, XX, XX, XX, XX },
    {  31, 12, 13, 30, XX, XX, XX, XX },
    };

G35StringWindowSmall::G35StringWindowSmall()
: G35String()
{
    DebugPrintf("G35StringWindowSmall\n");
}

light_count_t G35StringWindowSmall::get_light_count()
{
    switch (layout_)
    {
    case STRING_LAYOUT_SIDES:                   return SIDES_COUNT;
    case STRING_LAYOUT_HORIZONTAL_LINES:        return HORIZONTAL_LINES_COUNT;
    case STRING_LAYOUT_HORIZONTAL_LINES_CENTER: return HORIZONTAL_LINES_CENTER_COUNT;
    case STRING_LAYOUT_VERTICAL_LINES:          return VERTICAL_LINES_COUNT;
    case STRING_LAYOUT_VERTICAL_LINES_CENTER:   return VERTICAL_LINES_CENTER_COUNT;
    case STRING_LAYOUT_RINGS_CENTER:            return RINGS_CENTER_COUNT;
    case STRING_LAYOUT_RINGS_CORNER:            return RINGS_CORNER_COUNT;
    }

    // Any other unrecognized mode is treated as a linear string with a 1:1 mapping
    // between physical and virtual bulbs.
    return light_count_;
}

void G35StringWindowSmall::set_layout(STRING_LAYOUT layout)
{
    layout_ = layout;
}

void G35StringWindowSmall::set_color(light_count_t bulb, uint8_t intensity, color_t color)
{
    byte bulb_map_size;
    light_count_t *bulb_mapping = NULL;
    light_count_t physical_bulb;

    switch (layout_)
    {
    case STRING_LAYOUT_SIDES:
        bulb_map_size = SIDES_LENGTH;
        bulb_mapping = window_small_sides[bulb];
        break;
    case STRING_LAYOUT_HORIZONTAL_LINES:
        bulb_map_size = HORIZONTAL_LINES_LENGTH;
        bulb_mapping = window_small_horizontal_lines[bulb];
        break;
    case STRING_LAYOUT_HORIZONTAL_LINES_CENTER:
        bulb_map_size = HORIZONTAL_LINES_CENTER_LENGTH;
        bulb_mapping = window_small_horizontal_lines_center[bulb];
        break;
    case STRING_LAYOUT_VERTICAL_LINES:
        bulb_map_size = VERTICAL_LINES_LENGTH;
        bulb_mapping = window_small_vertical_lines[bulb];
        break;
    case STRING_LAYOUT_VERTICAL_LINES_CENTER:
        bulb_map_size = VERTICAL_LINES_CENTER_LENGTH;
        bulb_mapping = window_small_vertical_lines_center[bulb];
        break;
    case STRING_LAYOUT_RINGS_CENTER:
        bulb_map_size = RINGS_CENTER_LENGTH;
        bulb_mapping = window_small_rings_center[bulb];
        break;
    case STRING_LAYOUT_RINGS_CORNER:
        bulb_map_size = RINGS_CORNER_LENGTH;
        bulb_mapping = window_small_rings_corner[bulb];
        break;
    }

    switch (layout_)
    {
    default:
    case STRING_LAYOUT_LINEAR:
        G35String::set_color(bulb, intensity, color);
        break;

    case STRING_LAYOUT_SIDES:
    case STRING_LAYOUT_HORIZONTAL_LINES:
    case STRING_LAYOUT_HORIZONTAL_LINES_CENTER:
    case STRING_LAYOUT_VERTICAL_LINES:
    case STRING_LAYOUT_VERTICAL_LINES_CENTER:
    case STRING_LAYOUT_RINGS_CENTER:
    case STRING_LAYOUT_RINGS_CORNER:
        for (byte i = 0; i < bulb_map_size; i++)
        {
            physical_bulb = pgm_read_byte(&(bulb_mapping[i]));
            if (physical_bulb == XX)
            {
                break;
            }
            DebugPrintf("Setting Bulb: %u\n", physical_bulb);
            G35String::set_color(physical_bulb, intensity, color);
        }
        break;
    }
}


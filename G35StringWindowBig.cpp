
#include <DebugConfig.h>
#if DEBUG_G35
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <G35StringWindowBig.h>
#include <avr/pgmspace.h>

#define XX 0xFF

//  Window Big Layout
//  Left/Right = 14 bulbs
//  Top/Bottom = 11 bulbs
//
//       1   2   3   4   5   6   7   8   9  10  11  12  13
//    ----------------------------------------------------
// 14 | 13  14  15  16  17  18  19  20  21  22  23  24  25
// 13 | 12                                              26
// 12 | 11                                              27
// 11 | 10                                              28
// 10 |  9                                              29
//  9 |  8                                              30
//  8 |  7                                              31
//  7 |  6                                              32
//  6 |  5                                              33
//  5 |  4                                              34
//  4 |  3                                              35
//  3 |  2                                              36
//  2 |  1                                              37
//  1 |  0  49  48  47  46  45  44  43  42  41  40  39  38

// STRING_LAYOUT_SIDES
#define SIDES_COUNT 4
#define SIDES_LENGTH 14
PROGMEM prog_uchar window_big_sides[SIDES_COUNT][SIDES_LENGTH] = {
    {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13 },
    { 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, XX, XX, XX },
    { 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38 },
    { 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, XX, XX, XX },
    };

// STRING_LAYOUT_HORIZONTAL_LINES
#define HORIZONTAL_LINES_COUNT 14
#define HORIZONTAL_LINES_LENGTH 13
PROGMEM prog_uchar window_big_horizontal_lines[HORIZONTAL_LINES_COUNT][HORIZONTAL_LINES_LENGTH] = {
    {  0, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38 },
    {  1, 37, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  2, 36, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  3, 35, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  4, 34, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  5, 33, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  6, 32, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  7, 31, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  8, 30, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  9, 29, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 10, 28, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 11, 27, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 12, 26, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 },
    };

// STRING_LAYOUT_HORIZONTAL_LINES_CENTER
#define HORIZONTAL_LINES_CENTER_COUNT 7
#define HORIZONTAL_LINES_CENTER_LENGTH 26
PROGMEM prog_uchar window_big_horizontal_lines_center[HORIZONTAL_LINES_CENTER_COUNT][HORIZONTAL_LINES_CENTER_LENGTH] = {
    {  6, 32,  7, 31, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  5, 33,  8, 30, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  4, 34,  9, 29, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  3, 35, 10, 28, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  2, 36, 11, 27, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  1, 37, 12, 26, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  0, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 },
    };

// STRING_LAYOUT_VERTICAL_LINES
#define VERTICAL_LINES_COUNT 13
#define VERTICAL_LINES_LENGTH 14
PROGMEM prog_uchar window_big_vertical_lines[VERTICAL_LINES_COUNT][VERTICAL_LINES_LENGTH] = {
    {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13 },
    { 49, 14, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 48, 15, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 47, 16, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 46, 17, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 45, 18, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 44, 19, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 43, 20, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 42, 21, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 41, 22, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 40, 23, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 39, 24, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25 },
    };

// STRING_LAYOUT_VERTICAL_LINES_CENTER
#define VERTICAL_LINES_CENTER_COUNT 7
#define VERTICAL_LINES_CENTER_LENGTH 28
PROGMEM prog_uchar window_big_vertical_lines_center[VERTICAL_LINES_CENTER_COUNT][VERTICAL_LINES_CENTER_LENGTH] = {
    { 44, 19, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 45, 18, 43, 20, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 46, 17, 42, 21, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 47, 16, 41, 22, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 48, 15, 40, 23, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 49, 14, 39, 24, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25 },
    };

// STRING_LAYOUT_RINGS_CENTER
#define RINGS_CENTER_COUNT 13
#define RINGS_CENTER_LENGTH 4
PROGMEM prog_uchar window_big_rings_center[RINGS_CENTER_COUNT][RINGS_CENTER_LENGTH] = {
    { 44, 19, XX, XX },
    { 45, 18, 43, 20 },
    { 46, 17, 42, 21 },
    { 47, 16, 41, 22 },
    { 48, 15, 40, 23 },
    { 49, 14, 39, 24 },
    {  0, 13, 38, 25 },
    {  1, 12, 37, 26 },
    {  2, 11, 36, 27 },
    {  3, 10, 35, 28 },
    {  4,  9, 34, 29 },
    {  5,  8, 33, 30 },
    {  6,  7, 32, 31 },
    };

// STRING_LAYOUT_RINGS_CORNER
#define RINGS_CORNER_COUNT 7
#define RINGS_CORNER_LENGTH 8
PROGMEM prog_uchar window_big_rings_corner[RINGS_CORNER_COUNT][RINGS_CORNER_LENGTH] = {
    {  0, 13, 38, 25, XX, XX, XX, XX },
    {  1, 49, 12, 14, 39, 37, 26, 24 },
    {  2, 48, 11, 15, 40, 36, 27, 23 },
    {  3, 47, 10, 16, 41, 35, 28, 22 },
    {  4, 46,  9, 17, 42, 34, 29, 21 },
    {  5, 45,  8, 18, 43, 33, 30, 20 },
    {  6, 44,  7, 19, 32, 31, XX, XX },
    };

G35StringWindowBig::G35StringWindowBig()
: G35String()
{
    DebugPrintf("G35StringWindowBig\n");
}

light_count_t G35StringWindowBig::get_light_count()
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

void G35StringWindowBig::set_layout(STRING_LAYOUT layout)
{
    layout_ = layout;
}

void G35StringWindowBig::set_color(light_count_t bulb, uint8_t intensity, color_t color)
{
    byte bulb_map_size;
    light_count_t *bulb_mapping = NULL;
    light_count_t physical_bulb;

    switch (layout_)
    {
    case STRING_LAYOUT_SIDES:
        bulb_map_size = SIDES_LENGTH;
        bulb_mapping = window_big_sides[bulb];
        break;
    case STRING_LAYOUT_HORIZONTAL_LINES:
        bulb_map_size = HORIZONTAL_LINES_LENGTH;
        bulb_mapping = window_big_horizontal_lines[bulb];
        break;
    case STRING_LAYOUT_HORIZONTAL_LINES_CENTER:
        bulb_map_size = HORIZONTAL_LINES_CENTER_LENGTH;
        bulb_mapping = window_big_horizontal_lines_center[bulb];
        break;
    case STRING_LAYOUT_VERTICAL_LINES:
        bulb_map_size = VERTICAL_LINES_LENGTH;
        bulb_mapping = window_big_vertical_lines[bulb];
        break;
    case STRING_LAYOUT_VERTICAL_LINES_CENTER:
        bulb_map_size = VERTICAL_LINES_CENTER_LENGTH;
        bulb_mapping = window_big_vertical_lines_center[bulb];
        break;
    case STRING_LAYOUT_RINGS_CENTER:
        bulb_map_size = RINGS_CENTER_LENGTH;
        bulb_mapping = window_big_rings_center[bulb];
        break;
    case STRING_LAYOUT_RINGS_CORNER:
        bulb_map_size = RINGS_CORNER_LENGTH;
        bulb_mapping = window_big_rings_corner[bulb];
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


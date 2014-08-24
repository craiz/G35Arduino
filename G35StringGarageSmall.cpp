
#include <DebugConfig.h>
#if DEBUG_G35
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <G35StringGarageSmall.h>
#include <avr/pgmspace.h>

#define XX 0xFF

//  Garage Small Layout
//  Left/Right = 12 bulbs
//  Top Arch = 12 bulbs
//
//       1  2  3  4  5  6  7  8  9 10 11 12 13 14
//    -------------------------------------------
// 18 |                   17 18
// 17 |                16       19
// 16 |             15             20
// 15 |          14                   21
// 14 |       13                         22
// 13 |    12                               23
// 12 | 11                                     24
// 11 | 10                                     25
// 10 |  9                                     26  - 
//  9 |  8                                     27  - Horizontal center
//  8 |  7                                     28
//  7 |  6                                     29
//  6 |  5                                     30
//  5 |  4                                     31
//  4 |  3                                     32
//  3 |  2                                     33
//  2 |  1                                     34
//  1 |  0                                     35

// STRING_LAYOUT_SIDES
#define SIDES_COUNT 3
#define SIDES_LENGTH 12
PROGMEM prog_uchar garage_small_sides[SIDES_COUNT][SIDES_LENGTH] = {
    {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11 },
    { 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 },
    { 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 },
    };

// STRING_LAYOUT_HORIZONTAL_LINES
#define HORIZONTAL_LINES_COUNT 18
#define HORIZONTAL_LINES_LENGTH 2
PROGMEM prog_uchar garage_small_horizontal_lines[HORIZONTAL_LINES_COUNT][HORIZONTAL_LINES_LENGTH] = {
    {  0, 35 },
    {  1, 34 },
    {  2, 33 },
    {  3, 32 },
    {  4, 31 },
    {  5, 30 },
    {  6, 29 },
    {  7, 28 },
    {  8, 27 },
    {  9, 26 },
    { 10, 25 },
    { 11, 24 },
    { 12, 23 },
    { 13, 22 },
    { 14, 21 },
    { 15, 20 },
    { 16, 19 },
    { 17, 18 },
    };

// STRING_LAYOUT_HORIZONTAL_LINES_CENTER
#define HORIZONTAL_LINES_CENTER_COUNT 9
#define HORIZONTAL_LINES_CENTER_LENGTH 4
PROGMEM prog_uchar garage_small_horizontal_lines_center[HORIZONTAL_LINES_CENTER_COUNT][HORIZONTAL_LINES_CENTER_LENGTH] = {
    {  8, 27,  9, 26 },
    {  7, 28, 10, 25 },
    {  6, 29, 11, 24 },
    {  5, 30, 12, 23 },
    {  4, 31, 13, 22 },
    {  3, 32, 14, 21 },
    {  2, 33, 15, 20 },
    {  1, 34, 16, 19 },
    {  0, 35, 17, 18 },
    };

// STRING_LAYOUT_VERTICAL_LINES
#define VERTICAL_LINES_COUNT 14
#define VERTICAL_LINES_LENGTH 12
PROGMEM prog_uchar garage_small_vertical_lines[VERTICAL_LINES_COUNT][VERTICAL_LINES_LENGTH] = {
    {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11 },
    { 12, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 13, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 14, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 15, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 16, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 17, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 18, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 19, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 20, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 21, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 22, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 23, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 },
    };

// STRING_LAYOUT_VERTICAL_LINES_CENTER
#define VERTICAL_LINES_CENTER_COUNT 7
#define VERTICAL_LINES_CENTER_LENGTH 24
PROGMEM prog_uchar garage_small_vertical_lines_center[VERTICAL_LINES_CENTER_COUNT][VERTICAL_LINES_CENTER_LENGTH] = {
    { 17, 18, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 16, 19, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 15, 20, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 14, 21, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 13, 22, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 12, 23, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 },
    };

// STRING_LAYOUT_RINGS_CENTER
#define RINGS_CENTER_COUNT 18
#define RINGS_CENTER_LENGTH 2
PROGMEM prog_uchar garage_small_rings_center[RINGS_CENTER_COUNT][RINGS_CENTER_LENGTH] = {
    { 17, 18 },
    { 16, 19 },
    { 15, 20 },
    { 14, 21 },
    { 13, 22 },
    { 12, 23 },
    { 11, 24 },
    { 10, 25 },
    {  9, 26 },
    {  8, 27 },
    {  7, 28 },
    {  6, 29 },
    {  5, 30 },
    {  4, 31 },
    {  3, 32 },
    {  2, 33 },
    {  1, 34 },
    {  0, 35 },
    };

// STRING_LAYOUT_RINGS_CORNER
#define RINGS_CORNER_COUNT 12
#define RINGS_CORNER_LENGTH 4
PROGMEM prog_uchar garage_small_rings_corner[RINGS_CORNER_COUNT][RINGS_CORNER_LENGTH] = {
    { 11, 24, XX, XX },
    { 10, 12, 23, 25 },
    {  9, 13, 22, 26 },
    {  8, 14, 21, 27 },
    {  7, 15, 20, 28 },
    {  6, 16, 19, 29 },
    {  5, 17, 18, 30 },
    {  4, 31, XX, XX },
    {  3, 32, XX, XX },
    {  2, 33, XX, XX },
    {  1, 34, XX, XX },
    {  0, 35, XX, XX },
    };

G35StringGarageSmall::G35StringGarageSmall()
: G35String()
{
    DebugPrintf("G35StringGarageSmall\n");
}

light_count_t G35StringGarageSmall::get_light_count()
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

void G35StringGarageSmall::set_layout(STRING_LAYOUT layout)
{
    layout_ = layout;
}

void G35StringGarageSmall::set_color(light_count_t bulb, uint8_t intensity, color_t color)
{
    byte bulb_map_size;
    light_count_t *bulb_mapping = NULL;
    light_count_t physical_bulb;

    switch (layout_)
    {
    case STRING_LAYOUT_SIDES:
        bulb_map_size = SIDES_LENGTH;
        bulb_mapping = garage_small_sides[bulb];
        break;
    case STRING_LAYOUT_HORIZONTAL_LINES:
        bulb_map_size = HORIZONTAL_LINES_LENGTH;
        bulb_mapping = garage_small_horizontal_lines[bulb];
        break;
    case STRING_LAYOUT_HORIZONTAL_LINES_CENTER:
        bulb_map_size = HORIZONTAL_LINES_CENTER_LENGTH;
        bulb_mapping = garage_small_horizontal_lines_center[bulb];
        break;
    case STRING_LAYOUT_VERTICAL_LINES:
        bulb_map_size = VERTICAL_LINES_LENGTH;
        bulb_mapping = garage_small_vertical_lines[bulb];
        break;
    case STRING_LAYOUT_VERTICAL_LINES_CENTER:
        bulb_map_size = VERTICAL_LINES_CENTER_LENGTH;
        bulb_mapping = garage_small_vertical_lines_center[bulb];
        break;
    case STRING_LAYOUT_RINGS_CENTER:
        bulb_map_size = RINGS_CENTER_LENGTH;
        bulb_mapping = garage_small_rings_center[bulb];
        break;
    case STRING_LAYOUT_RINGS_CORNER:
        bulb_map_size = RINGS_CORNER_LENGTH;
        bulb_mapping = garage_small_rings_corner[bulb];
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


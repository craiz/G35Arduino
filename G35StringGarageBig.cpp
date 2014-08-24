
#include <DebugConfig.h>
#if DEBUG_G35
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <G35StringGarageBig.h>
#include <avr/pgmspace.h>

#define XX 0xFF

//  Garage Big Layout
//  Left/Right = 12 bulbs
//  Top Arch = 26 bulbs
//
//       1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28
//    -------------------------------------------------------------------------------------
// 25 |                                        24 25
// 24 |                                     23       26
// 23 |                                  22             27
// 22 |                               21                   28
// 21 |                            20                         29
// 20 |                         19                               30
// 19 |                      18                                     31
// 18 |                   17                                           32
// 17 |                16                                                 33
// 16 |             15                                                       34 
// 15 |          14                                                             35
// 14 |       13                                                                   36
// 13 |    12                                                                         37
// 12 | 11                                                                               38
// 11 | 10                                                                               39
// 10 |  9                                                                               40  -
//  9 |  8                                                                               41  - Horizontal Center
//  8 |  7                                                                               42
//  7 |  6                                                                               43
//  6 |  5                                                                               44
//  5 |  4                                                                               45
//  4 |  3                                                                               46
//  3 |  2                                                                               47
//  2 |  1                                                                               48
//  1 |  0                                                                               49


// STRING_LAYOUT_SIDES
#define SIDES_COUNT 3
#define SIDES_LENGTH 26
PROGMEM prog_uchar garage_big_sides[SIDES_COUNT][SIDES_LENGTH] = {
    {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37 },
    { 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    };

// STRING_LAYOUT_HORIZONTAL_LINES
#define HORIZONTAL_LINES_COUNT 18
#define HORIZONTAL_LINES_LENGTH 6
PROGMEM prog_uchar garage_big_horizontal_lines[HORIZONTAL_LINES_COUNT][HORIZONTAL_LINES_LENGTH] = {
    {  0, 49, XX, XX, XX, XX },
    {  1, 48, XX, XX, XX, XX },
    {  2, 47, XX, XX, XX, XX },
    {  3, 46, XX, XX, XX, XX },
    {  4, 45, XX, XX, XX, XX },
    {  5, 44, XX, XX, XX, XX },
    {  6, 43, XX, XX, XX, XX },
    {  7, 42, XX, XX, XX, XX },
    {  8, 41, XX, XX, XX, XX },
    {  9, 40, XX, XX, XX, XX },
    { 10, 39, XX, XX, XX, XX },
    { 11, 38, XX, XX, XX, XX },
    { 12, 37, 13, 36, XX, XX },
    { 14, 35, 15, 34, XX, XX }, 
    { 16, 33, 17, 32, XX, XX },
    { 18, 31, 19, 30, XX, XX },
    { 20, 29, 21, 28, XX, XX },
    { 22, 27, 23, 26, 24, 25 },
    };

// STRING_LAYOUT_HORIZONTAL_LINES_CENTER
#define HORIZONTAL_LINES_CENTER_COUNT 9
#define HORIZONTAL_LINES_CENTER_LENGTH 8
PROGMEM prog_uchar garage_big_horizontal_lines_center[HORIZONTAL_LINES_CENTER_COUNT][HORIZONTAL_LINES_CENTER_LENGTH] = {
    {  8, 41,  9, 40, XX, XX, XX, XX },
    {  7, 42, 10, 39, XX, XX, XX, XX },
    {  6, 43, 11, 38, XX, XX, XX, XX },
    {  5, 44, 12, 37, 13, 36, XX, XX },
    {  4, 45, 14, 35, 15, 34, XX, XX },
    {  3, 46, 16, 33, 17, 32, XX, XX },
    {  2, 47, 18, 31, 19, 30, XX, XX },
    {  1, 48, 20, 29, 21, 28, XX, XX },
    {  0, 59, 22, 27, 23, 26, 24, 25 },
    };

// STRING_LAYOUT_VERTICAL_LINES
#define VERTICAL_LINES_COUNT 28
#define VERTICAL_LINES_LENGTH 12
PROGMEM prog_uchar garage_big_vertical_lines[VERTICAL_LINES_COUNT][VERTICAL_LINES_LENGTH] = {
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
    { 24, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 25, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 26, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 27, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 28, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 29, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 30, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 31, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 32, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 33, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 34, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 35, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 36, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 37, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49 },
    };

// STRING_LAYOUT_VERTICAL_LINES_CENTER
#define VERTICAL_LINES_CENTER_COUNT 14
#define VERTICAL_LINES_CENTER_LENGTH 24
PROGMEM prog_uchar garage_big_vertical_lines_center[VERTICAL_LINES_CENTER_COUNT][VERTICAL_LINES_CENTER_LENGTH] = {
    { 24, 25, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 23, 26, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 22, 27, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 21, 28, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 20, 29, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 19, 30, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 18, 31, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 17, 32, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 16, 33, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 15, 34, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 14, 35, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 13, 36, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 12, 37, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49 },
    };

// STRING_LAYOUT_RINGS_CENTER
#define RINGS_CENTER_COUNT 25
#define RINGS_CENTER_LENGTH 2
PROGMEM prog_uchar garage_big_rings_center[RINGS_CENTER_COUNT][RINGS_CENTER_LENGTH] = {
    { 24, 25 },
    { 23, 26 },
    { 22, 27 },
    { 21, 28 },
    { 20, 29 },
    { 19, 30 },
    { 18, 31 },
    { 17, 32 },
    { 16, 33 },
    { 15, 34 },
    { 14, 35 },
    { 13, 36 },
    { 12, 37 },
    { 11, 38 },
    { 10, 39 },
    {  9, 40 },
    {  8, 41 },
    {  7, 42 },
    {  6, 43 },
    {  5, 44 },
    {  4, 45 },
    {  3, 46 },
    {  2, 47 },
    {  1, 48 },
    {  0, 49 },
    };

// STRING_LAYOUT_RINGS_CORNER
#define RINGS_CORNER_COUNT 14
#define RINGS_CORNER_LENGTH 4
PROGMEM prog_uchar garage_big_rings_corner[RINGS_CORNER_COUNT][RINGS_CORNER_LENGTH] = {
    { 11, 24, XX, XX },
    { 10, 12, 39, 37 },
    {  9, 13, 40, 36 },
    {  8, 14, 41, 35 },
    {  7, 15, 42, 34 },
    {  6, 16, 43, 33 },
    {  5, 17, 44, 32 },
    {  4, 18, 45, 31 },
    {  3, 19, 46, 30 },
    {  2, 20, 47, 29 },
    {  1, 21, 48, 28 },
    {  0, 22, 49, 27 },
    { 23, 26, XX, XX },
    { 24, 25, XX, XX },
    };

G35StringGarageBig::G35StringGarageBig()
: G35String()
{
    DebugPrintf("G35StringGarageBig\n");
}

light_count_t G35StringGarageBig::get_light_count()
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

void G35StringGarageBig::set_layout(STRING_LAYOUT layout)
{
    layout_ = layout;
}

void G35StringGarageBig::set_color(light_count_t bulb, uint8_t intensity, color_t color)
{
    byte bulb_map_size;
    light_count_t *bulb_mapping = NULL;
    light_count_t physical_bulb;

    switch (layout_)
    {
    case STRING_LAYOUT_SIDES:
        bulb_map_size = SIDES_LENGTH;
        bulb_mapping = garage_big_sides[bulb];
        break;
    case STRING_LAYOUT_HORIZONTAL_LINES:
        bulb_map_size = HORIZONTAL_LINES_LENGTH;
        bulb_mapping = garage_big_horizontal_lines[bulb];
        break;
    case STRING_LAYOUT_HORIZONTAL_LINES_CENTER:
        bulb_map_size = HORIZONTAL_LINES_CENTER_LENGTH;
        bulb_mapping = garage_big_horizontal_lines_center[bulb];
        break;
    case STRING_LAYOUT_VERTICAL_LINES:
        bulb_map_size = VERTICAL_LINES_LENGTH;
        bulb_mapping = garage_big_vertical_lines[bulb];
        break;
    case STRING_LAYOUT_VERTICAL_LINES_CENTER:
        bulb_map_size = VERTICAL_LINES_CENTER_LENGTH;
        bulb_mapping = garage_big_vertical_lines_center[bulb];
        break;
    case STRING_LAYOUT_RINGS_CENTER:
        bulb_map_size = RINGS_CENTER_LENGTH;
        bulb_mapping = garage_big_rings_center[bulb];
        break;
    case STRING_LAYOUT_RINGS_CORNER:
        bulb_map_size = RINGS_CORNER_LENGTH;
        bulb_mapping = garage_big_rings_corner[bulb];
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
                break;;
            }
            DebugPrintf("Setting Bulb: %u\n", physical_bulb);
            G35String::set_color(physical_bulb, intensity, color);
        }
        break;
    }
}


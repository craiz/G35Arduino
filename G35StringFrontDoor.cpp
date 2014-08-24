
#include <DebugConfig.h>
#if DEBUG_G35
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <G35StringFrontDoor.h>
#include <avr/pgmspace.h>

#define XX 0xFF

//  Front Door Layout
//  Left/Right = 21 bulbs
//  Top Arch = 8 bulbs
//
//       1  2  3  4  5  6  7  8  9 10
//    -------------------------------
// 25 |             24 25            
// 24 |          23       26         
// 23 |       22             27      
// 22 |    21                   28   
// 21 | 20                         29
// 20 | 19                         30
// 19 | 18                         31
// 18 | 17                         32
// 17 | 16                         33
// 16 | 15                         34
// 15 | 14                         35
// 14 | 13                         36
// 13 | 12                         37  - Horizontal Center
// 12 | 11                         38
// 11 | 10                         39
// 10 |  9                         40
//  9 |  8                         41
//  8 |  7                         42
//  7 |  6                         43
//  6 |  5                         44
//  5 |  4                         45
//  4 |  3                         46
//  3 |  2                         47
//  2 |  1                         48
//  1 |  0                         49


// STRING_LAYOUT_SIDES
#define SIDES_COUNT 3
#define SIDES_LENGTH 21
PROGMEM prog_uchar front_door_sides[SIDES_COUNT][SIDES_LENGTH] = {
    {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 },
    { 21, 22, 23, 24, 25, 26, 27, 28, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49 },
    };

// STRING_LAYOUT_HORIZONTAL_LINES
#define HORIZONTAL_LINES_COUNT 25
#define HORIZONTAL_LINES_LENGTH 2
PROGMEM prog_uchar front_door_horizontal_lines[HORIZONTAL_LINES_COUNT][HORIZONTAL_LINES_LENGTH] = {
    {  0, 49 },
    {  1, 48 },
    {  2, 47 },
    {  3, 46 },
    {  4, 45 },
    {  5, 44 },
    {  6, 43 },
    {  7, 42 },
    {  8, 41 },
    {  9, 40 },
    { 10, 39 },
    { 11, 38 },
    { 12, 37 },
    { 13, 36 }, 
    { 14, 35 },
    { 15, 34 },
    { 16, 33 },
    { 17, 32 },
    { 18, 31 },
    { 19, 30 },
    { 20, 29 },
    { 21, 28 },
    { 22, 27 },
    { 23, 26 },
    { 24, 25 },
    };

// STRING_LAYOUT_HORIZONTAL_LINES_CENTER
#define HORIZONTAL_LINES_CENTER_COUNT 13
#define HORIZONTAL_LINES_CENTER_LENGTH 4
PROGMEM prog_uchar front_door_horizontal_lines_center[HORIZONTAL_LINES_CENTER_COUNT][HORIZONTAL_LINES_CENTER_LENGTH] = {
    { 12, 37, XX, XX },
    { 13, 36, 11, 38 },
    { 14, 35, 10, 39 },
    { 15, 34,  9, 40 },
    { 16, 33,  8, 41 },
    { 17, 32,  7, 42 },
    { 18, 31,  6, 43 },
    { 19, 30,  5, 44 },
    { 20, 29,  4, 45 },
    { 21, 28,  3, 46 },
    { 22, 27,  2, 47 },
    { 23, 26,  1, 48 },
    { 24, 25,  0, 49 },
    };

// STRING_LAYOUT_VERTICAL_LINES
#define VERTICAL_LINES_COUNT 10
#define VERTICAL_LINES_LENGTH 21
PROGMEM prog_uchar front_door_vertical_lines[VERTICAL_LINES_COUNT][VERTICAL_LINES_LENGTH] = {
    {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 },
    { 21, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 22, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 23, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 24, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 25, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 26, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 27, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 28, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49 },
    };

// STRING_LAYOUT_VERTICAL_LINES_CENTER
#define VERTICAL_LINES_CENTER_COUNT 5
#define VERTICAL_LINES_CENTER_LENGTH 42
PROGMEM prog_uchar front_door_vertical_lines_center[VERTICAL_LINES_CENTER_COUNT][VERTICAL_LINES_CENTER_LENGTH] = {
    { 24, 25, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 23, 26, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 22, 27, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    { 21, 28, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX },
    {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49 },
    };

// STRING_LAYOUT_RINGS_CENTER
#define RINGS_CENTER_COUNT 25
#define RINGS_CENTER_LENGTH 2
PROGMEM prog_uchar front_door_rings_center[RINGS_CENTER_COUNT][RINGS_CENTER_LENGTH] = {
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
#define RINGS_CORNER_COUNT 21
#define RINGS_CORNER_LENGTH 4
PROGMEM prog_uchar front_door_rings_corner[RINGS_CORNER_COUNT][RINGS_CORNER_LENGTH] = {
    { 20, 29, XX, XX },
    { 19, 30, 21, 28 },
    { 18, 31, 22, 27 },
    { 17, 32, 23, 26 },
    { 16, 33, 24, 25 },
    { 15, 34, XX, XX },
    { 14, 35, XX, XX },
    { 13, 36, XX, XX },
    { 12, 37, XX, XX },
    { 11, 38, XX, XX },
    { 10, 39, XX, XX },
    {  9, 40, XX, XX },
    {  8, 41, XX, XX },
    {  7, 42, XX, XX },
    {  6, 43, XX, XX },
    {  5, 44, XX, XX },
    {  4, 45, XX, XX },
    {  3, 46, XX, XX },
    {  2, 47, XX, XX },
    {  1, 48, XX, XX },
    {  0, 49, XX, XX },
    };

G35StringFrontDoor::G35StringFrontDoor()
: G35String()
{
    DebugPrintf("G35StringFrontDoor\n");
}

light_count_t G35StringFrontDoor::get_light_count()
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

void G35StringFrontDoor::set_layout(STRING_LAYOUT layout)
{
    layout_ = layout;
}

void G35StringFrontDoor::set_color(light_count_t bulb, uint8_t intensity, color_t color)
{
    byte bulb_map_size;
    light_count_t *bulb_mapping = NULL;
    light_count_t physical_bulb;

    switch (layout_)
    {
    case STRING_LAYOUT_SIDES:
        bulb_map_size = SIDES_LENGTH;
        bulb_mapping = front_door_sides[bulb];
        break;
    case STRING_LAYOUT_HORIZONTAL_LINES:
        bulb_map_size = HORIZONTAL_LINES_LENGTH;
        bulb_mapping = front_door_horizontal_lines[bulb];
        break;
    case STRING_LAYOUT_HORIZONTAL_LINES_CENTER:
        bulb_map_size = HORIZONTAL_LINES_CENTER_LENGTH;
        bulb_mapping = front_door_horizontal_lines_center[bulb];
        break;
    case STRING_LAYOUT_VERTICAL_LINES:
        bulb_map_size = VERTICAL_LINES_LENGTH;
        bulb_mapping = front_door_vertical_lines[bulb];
        break;
    case STRING_LAYOUT_VERTICAL_LINES_CENTER:
        bulb_map_size = VERTICAL_LINES_CENTER_LENGTH;
        bulb_mapping = front_door_vertical_lines_center[bulb];
        break;
    case STRING_LAYOUT_RINGS_CENTER:
        bulb_map_size = RINGS_CENTER_LENGTH;
        bulb_mapping = front_door_rings_center[bulb];
        break;
    case STRING_LAYOUT_RINGS_CORNER:
        bulb_map_size = RINGS_CORNER_LENGTH;
        bulb_mapping = front_door_rings_corner[bulb];
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


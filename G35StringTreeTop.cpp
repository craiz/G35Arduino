
#include <DebugConfig.h>
#if DEBUG_G35
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <G35StringTreeTop.h>
#include <avr/pgmspace.h>

#define XX 0xFF


//  Tree Top Layout
//  Facet = 7 bulbs
//
// Each column represents a facet of the diamond.
//
//       1  2  3  4  5  6  7
//    ----------------------
//  5 |  4  5 14 15 24 25 34
//  4 |  3  6 13 16 23 26 33
//  3 |  2  7 12 17 22 27 32
//  2 |  1  8 11 18 21 28 31
//  1 |  0  9 10 19 20 29 30
//
// Each facet is configured as a triangle.
//
//       1  2  3
//    ----------
//  5 |        4
//  4 |     3   
//  3 |  2      
//  2 |     1   
//  1 |        0
//


// STRING_LAYOUT_SIDES
#define SIDES_COUNT 7
#define SIDES_LENGTH 5
PROGMEM prog_uchar tree_top_sides[SIDES_COUNT][SIDES_LENGTH] = {
    {  0,  1,  2,  3,  4 },
    {  5,  6,  7,  8,  9 },
    { 10, 11, 12, 13, 14 },
    { 15, 16, 17, 18, 19 },
    { 20, 21, 22, 23, 24 },
    { 25, 26, 27, 28, 29 },
    { 30, 31, 32, 33, 34 },
    };

// STRING_LAYOUT_HORIZONTAL_LINES
#define HORIZONTAL_LINES_COUNT  5
#define HORIZONTAL_LINES_LENGTH 7
PROGMEM prog_uchar tree_top_horizontal_lines[HORIZONTAL_LINES_COUNT][HORIZONTAL_LINES_LENGTH] = {
    {  0,  9, 10, 19, 20, 29, 30 },
    {  1,  8, 11, 18, 21, 28, 31 },
    {  2,  7, 12, 17, 22, 27, 32 },
    {  3,  6, 13, 16, 23, 26, 33 },
    {  4,  5, 14, 15, 24, 25, 34 },
    };

// STRING_LAYOUT_HORIZONTAL_LINES_CENTER
#define HORIZONTAL_LINES_CENTER_COUNT 3
#define HORIZONTAL_LINES_CENTER_LENGTH 14
PROGMEM prog_uchar tree_top_horizontal_lines_center[HORIZONTAL_LINES_CENTER_COUNT][HORIZONTAL_LINES_CENTER_LENGTH] = {
    {  2,  7, 12, 17, 22, 27, 32, XX, XX, XX, XX, XX, XX, XX },
    {  1,  8, 11, 18, 21, 28, 31,  3,  6, 13, 16, 23, 26, 33 },
    {  0,  9, 10, 19, 20, 29, 30,  4,  5, 14, 15, 24, 25, 34 },
    };

// STRING_LAYOUT_VERTICAL_LINES
#define VERTICAL_LINES_COUNT SIDES_COUNT
#define VERTICAL_LINES_LENGTH SIDES_LENGTH

// STRING_LAYOUT_VERTICAL_LINES_CENTER
#define VERTICAL_LINES_CENTER_COUNT 4
#define VERTICAL_LINES_CENTER_LENGTH 10
PROGMEM prog_uchar tree_top_vertical_lines_center[VERTICAL_LINES_CENTER_COUNT][VERTICAL_LINES_CENTER_LENGTH] = {
    { 15, 16, 17, 18, 19, XX, XX, XX, XX, XX },
    { 10, 11, 12, 13, 14, 20, 21, 22, 23, 24 },
    {  5,  6,  7,  8,  9, 25, 26, 27, 28, 29 },
    {  0,  1,  2,  3,  4, 30, 31, 32, 33, 34 },
    };

// STRING_LAYOUT_RINGS_CENTER
#define RINGS_CENTER_COUNT HORIZONTAL_LINES_CENTER_COUNT
#define RINGS_CENTER_LENGTH HORIZONTAL_LINES_CENTER_LENGTH

// STRING_LAYOUT_RINGS_CORNER
#define RINGS_CORNER_COUNT HORIZONTAL_LINES_CENTER_COUNT
#define RINGS_CORNER_LENGTH HORIZONTAL_LINES_CENTER_LENGTH

// STRING_LAYOUT_TREE_TOP_DOWN_LEFT_TO_RIGHT
#define DLTR_COUNT 35
#define DLTR_LENGTH 1
PROGMEM prog_uchar tree_top_down_left_to_right[DLTR_COUNT][DLTR_LENGTH] = {
    {  4 }, {  3 }, {  2 }, {  1 }, {  0 },
    {  5 }, {  6 }, {  7 }, {  8 }, {  9 },
    { 14 }, { 13 }, { 12 }, { 11 }, { 10 },
    { 15 }, { 16 }, { 17 }, { 18 }, { 19 },
    { 24 }, { 23 }, { 22 }, { 21 }, { 20 },
    { 25 }, { 26 }, { 27 }, { 28 }, { 29 },
    { 34 }, { 33 }, { 32 }, { 31 }, { 30 },
    };

// STRING_LAYOUT_TREE_TOP_UP_LEFT_TO_RIGHT
#define ULTR_COUNT 35
#define ULTR_LENGTH 1
PROGMEM prog_uchar tree_top_up_left_to_right[ULTR_COUNT][ULTR_LENGTH] = {
    {  0 }, {  1 }, {  2 }, {  3 }, {  4 },
    {  9 }, {  8 }, {  7 }, {  6 }, {  5 },
    { 10 }, { 11 }, { 12 }, { 13 }, { 14 },
    { 19 }, { 18 }, { 17 }, { 16 }, { 15 },
    { 20 }, { 21 }, { 22 }, { 23 }, { 24 },
    { 29 }, { 28 }, { 27 }, { 26 }, { 25 },
    { 30 }, { 31 }, { 32 }, { 33 }, { 34 },
    };

// STRING_LAYOUT_TREE_TOP_DOWN_RIGHT_TO_LEFT
#define DRTL_COUNT 35
#define DRTL_LENGTH 1
PROGMEM prog_uchar tree_top_down_right_to_left[DRTL_COUNT][DRTL_LENGTH] = {
    { 34 }, { 33 }, { 32 }, { 31 }, { 30 },
    { 25 }, { 26 }, { 27 }, { 28 }, { 29 },
    { 24 }, { 23 }, { 22 }, { 21 }, { 20 },
    { 15 }, { 16 }, { 17 }, { 18 }, { 19 },
    { 14 }, { 13 }, { 12 }, { 11 }, { 10 },
    {  5 }, {  6 }, {  7 }, {  8 }, {  9 },
    {  4 }, {  3 }, {  2 }, {  1 }, {  0 },
    };

// STRING_LAYOUT_TREE_TOP_UP_RIGHT_TO_LEFT
#define URTL_COUNT 35
#define URTL_LENGTH 1
PROGMEM prog_uchar tree_top_up_right_to_left[URTL_COUNT][URTL_LENGTH] = {
    { 30 }, { 31 }, { 32 }, { 33 }, { 34 },
    { 29 }, { 28 }, { 27 }, { 26 }, { 25 },
    { 20 }, { 21 }, { 22 }, { 23 }, { 24 },
    { 19 }, { 18 }, { 17 }, { 16 }, { 15 },
    { 10 }, { 11 }, { 12 }, { 13 }, { 14 },
    {  9 }, {  8 }, {  7 }, {  6 }, {  5 },
    {  0 }, {  1 }, {  2 }, {  3 }, {  4 },
    };

G35StringTreeTop::G35StringTreeTop()
: G35String()
{
    DebugPrintf("G35StringTreeTop\n");
}

light_count_t G35StringTreeTop::get_light_count()
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
    case STRING_LAYOUT_TREE_TOP_DOWN_LEFT_TO_RIGHT: return DLTR_COUNT;
    case STRING_LAYOUT_TREE_TOP_UP_LEFT_TO_RIGHT:   return ULTR_COUNT;
    case STRING_LAYOUT_TREE_TOP_DOWN_RIGHT_TO_LEFT: return DRTL_COUNT;
    case STRING_LAYOUT_TREE_TOP_UP_RIGHT_TO_LEFT:   return URTL_COUNT;
    }

    // Any other unrecognized mode is treated as a linear string with a 1:1 mapping
    // between physical and virtual bulbs.
    return light_count_;
}

void G35StringTreeTop::set_layout(STRING_LAYOUT layout)
{
    layout_ = layout;
}

void G35StringTreeTop::set_color(light_count_t bulb, uint8_t intensity, color_t color)
{
    byte bulb_map_size;
    light_count_t *bulb_mapping = NULL;
    light_count_t physical_bulb;

    switch (layout_)
    {
    case STRING_LAYOUT_SIDES:
        bulb_map_size = SIDES_LENGTH;
        bulb_mapping = tree_top_sides[bulb];
        break;
    case STRING_LAYOUT_HORIZONTAL_LINES:
        bulb_map_size = HORIZONTAL_LINES_LENGTH;
        bulb_mapping = tree_top_horizontal_lines[bulb];
        break;
    case STRING_LAYOUT_HORIZONTAL_LINES_CENTER:
        bulb_map_size = HORIZONTAL_LINES_CENTER_LENGTH;
        bulb_mapping = tree_top_horizontal_lines_center[bulb];
        break;
    case STRING_LAYOUT_VERTICAL_LINES:
        bulb_map_size = VERTICAL_LINES_LENGTH;
        bulb_mapping = tree_top_sides[bulb];
        break;
    case STRING_LAYOUT_VERTICAL_LINES_CENTER:
        bulb_map_size = VERTICAL_LINES_CENTER_LENGTH;
        bulb_mapping = tree_top_vertical_lines_center[bulb];
        break;
    case STRING_LAYOUT_RINGS_CENTER:
        bulb_map_size = RINGS_CENTER_LENGTH;
        bulb_mapping = tree_top_horizontal_lines_center[bulb];
        break;
    case STRING_LAYOUT_RINGS_CORNER:
        bulb_map_size = RINGS_CORNER_LENGTH;
        bulb_mapping = tree_top_horizontal_lines_center[bulb];
        break;
    case STRING_LAYOUT_TREE_TOP_DOWN_LEFT_TO_RIGHT:
        bulb_map_size = DLTR_LENGTH;
        bulb_mapping = tree_top_down_left_to_right[bulb];
        break;
    case STRING_LAYOUT_TREE_TOP_UP_LEFT_TO_RIGHT:
        bulb_map_size = ULTR_LENGTH;
        bulb_mapping = tree_top_up_left_to_right[bulb];
        break;
    case STRING_LAYOUT_TREE_TOP_DOWN_RIGHT_TO_LEFT:
        bulb_map_size = DRTL_LENGTH;
        bulb_mapping = tree_top_down_right_to_left[bulb];
        break;
    case STRING_LAYOUT_TREE_TOP_UP_RIGHT_TO_LEFT:
        bulb_map_size = URTL_LENGTH;
        bulb_mapping = tree_top_up_right_to_left[bulb];
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
    case STRING_LAYOUT_TREE_TOP_DOWN_LEFT_TO_RIGHT:
    case STRING_LAYOUT_TREE_TOP_UP_LEFT_TO_RIGHT:
    case STRING_LAYOUT_TREE_TOP_DOWN_RIGHT_TO_LEFT:
    case STRING_LAYOUT_TREE_TOP_UP_RIGHT_TO_LEFT:

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


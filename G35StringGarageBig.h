#ifndef INCLUDE_G35_STRING_GARAGE_BIG_H
#define INCLUDE_G35_STRING_GARAGE_BIG_H

#include <G35String.h>

// A G35StringGarageBig knows how to be a GE Color Effects light string of 50 bulbs
// configured as the outline of a double garage door.  The bulbs are laid out as follows:
//
// The string originates (bulb 0) in the bottom left corner.
// Left and right sides are vertical lines consisting of 12 bulbs each.
// Top is a curved line of 26 bulbs.
//
// It overrides the set_color() and get_light_count() methods to enable representing
// a group of physical bulbs in the sculpture as a single virtual bulb.
class G35StringGarageBig : public G35String
{
public:
    G35StringGarageBig();

    // G35 interface overrides
    virtual light_count_t get_light_count();
    virtual void set_color(light_count_t bulb, uint8_t intensity, color_t color);
    virtual void set_layout(STRING_LAYOUT layout);
};

#endif  // INCLUDE_G35_STRING_GARAGE_BIG_H


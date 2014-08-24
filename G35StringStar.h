#ifndef INCLUDE_G35_STRING_STAR_H
#define INCLUDE_G35_STRING_STAR_H

#include <G35String.h>

// A G35StringStar knows how to be a GE Color Effects light string of 50
// bulbs configured as a 5 pointed star.
//
// It overrides the set_color() and get_light_count() methods to enable representing
// a group of physical bulbs in the sculpture as a single virtual bulb.
class G35StringStar : public G35String
{
public:
    G35StringStar();

    // G35 interface overrides
    virtual light_count_t get_light_count();
    virtual void set_color(light_count_t bulb, uint8_t intensity, color_t color);
};

#endif  // INCLUDE_G35_STRING_STAR_H


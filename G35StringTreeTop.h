#ifndef INCLUDE_G35_STRING_TREE_TOP_H
#define INCLUDE_G35_STRING_TREE_TOP_H

#include <G35String.h>

// A G35StringTreeTop knows how to be a GE Color Effects light string of 35 bulbs.
// The string is configured as a 7-faceted diamond.  Each facet consists of 5 bubls.
//
// It overrides the set_color() and get_light_count() methods to enable representing
// a group of physical bulbs in the sculpture as a single virtual bulb.
class G35StringTreeTop : public G35String
{
public:
    G35StringTreeTop();

    // G35 interface overrides
    virtual light_count_t get_light_count();
    virtual void set_color(light_count_t bulb, uint8_t intensity, color_t color);
    virtual void set_layout(STRING_LAYOUT layout);
};

#endif  // INCLUDE_G35_STRING_TREE_TOP_H


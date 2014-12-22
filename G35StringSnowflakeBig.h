#ifndef INCLUDE_G35_STRING_SNOWFLAKE_BIG_H
#define INCLUDE_G35_STRING_SNOWFLAKE_BIG_H

#include <G35String.h>

// A G35StringSnowflakeBig knows how to be a GE Color Effects light string of 61
// bulbs configured as a 6 armed snowflake.
//
// It overrides the set_color() and get_light_count() methods to enable representing
// a group of physical bulbs in the sculpture as a single virtual bulb.
class G35StringSnowflakeBig : public G35String
{
public:
    G35StringSnowflakeBig();

    // G35 interface overrides
    virtual light_count_t get_light_count();
    virtual void set_color(light_count_t bulb, uint8_t intensity, color_t color);
    virtual void set_layout(STRING_LAYOUT layout);
};

#endif  // INCLUDE_G35_STRING_SNOWFLAKE_BIG_H


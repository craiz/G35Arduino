#ifndef INCLUDE_G35_STRING_SIMULATOR_H
#define INCLUDE_G35_STRING_SIMULATOR_H

#include <G35String.h>
#include <G35StringWindowSmall.h>

class G35StringSimulator : public G35StringWindowSmall
{
public:
    G35StringSimulator();

    // G35String interface overrides
    virtual void Configure(uint8_t pin, light_count_t light_count, light_count_t physical_light_count,
            light_count_t bulb_zero, bool is_forward, STRING_LAYOUT layout);

    // G35 interface overrides
    virtual light_count_t get_light_count();
    virtual void set_color(light_count_t bulb, uint8_t intensity, color_t color);

    color_t get_color(light_count_t bulb);

private:
    color_t *m_colors;
};

#endif  // INCLUDE_G35_STRING_SIMULATOR_H


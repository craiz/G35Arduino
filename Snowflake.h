
#ifndef INCLUDE_G35_PROGRAMS_SNOWFLAKE_H
#define INCLUDE_G35_PROGRAMS_SNOWFLAKE_H

#include <LightProgram.h>
#include <WaveUtils.h>
#include <ColorNodeCommands.h>
#include <G35StringSnowflakeBig.h>



typedef enum
{
    SNOWFLAKE_SECTION_ARMS = 0,
    SNOWFLAKE_SECTION_TIPS = 1,
} SNOWFLAKE_SECTION;


class G35SnowflakeBigSection : public G35
{
public:
    G35SnowflakeBigSection(G35& g35, SNOWFLAKE_SECTION section);

    // G35 interface overrides
    virtual light_count_t get_light_count();
    virtual void set_light_count(light_count_t light_count);
    virtual void set_color(light_count_t bulb, uint8_t intensity, color_t color);
    virtual light_count_t get_broadcast_bulb();

private:

    G35& m_g35;
    SNOWFLAKE_SECTION m_section;
};


class Snowflake : public LightProgram
{
public:
    Snowflake(G35& g35);
    ~Snowflake();
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    void Uninitialize();
    uint32_t Do();

private:

    G35SnowflakeBigSection m_Arms;
    G35SnowflakeBigSection m_Tips;
};

#endif // INCLUDE_G35_PROGRAMS_SNOWFLAKE_H


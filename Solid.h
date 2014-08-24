#ifndef INCLUDE_G35_PROGRAMS_SOLID_H
#define INCLUDE_G35_PROGRAMS_SOLID_H

#include <LightProgram.h>
#include <StockPrograms.h>
#include <ColorUtils.h>

class Solid : public SingleColorProgram
{
public:
    Solid(G35& g35);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    void Update(pattern_t pattern, option_t option, delay_t delay);
    void Kick();
    void Reset();
    uint32_t Do();

private:
    uint8_t m_Intensity;
    bool m_Done;
};

#endif  // INCLUDE_G35_PROGRAMS_SOLID_H


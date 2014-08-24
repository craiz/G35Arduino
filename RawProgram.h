#ifndef INCLUDE_G35_PROGRAMS_RAW_H
#define INCLUDE_G35_PROGRAMS_RAW_H

#include <LightProgram.h>
#include <ColorNodeCommands.h>


// 0-47 = Rainbow colors


class RawProgram : public LightProgram
{
public:
    RawProgram(G35& g35, RawCommand *pCommand);
    uint32_t Do();

private:

    RawCommand *m_pCommand;
    light_count_t m_loopCounter;
    light_count_t m_lightCount;
};

#endif  // INCLUDE_G35_PROGRAMS_RAW_H


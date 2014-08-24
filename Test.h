#ifndef INCLUDE_G35_PROGRAMS_TEST_H
#define INCLUDE_G35_PROGRAMS_TEST_H

#include <LightProgram.h>
#include <G35String.h>

class Test : public LightProgram
{
public:
    Test(G35String& g35String);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    void Update(pattern_t pattern, option_t option, delay_t delay);
    void Kick();
    void Reset();
    uint32_t Do();

private:

    G35String& m_G35String;
};

#endif  // INCLUDE_G35_PROGRAMS_TEST_H


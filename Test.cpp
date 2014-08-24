
#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_TEST
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <Test.h>

Test::Test(G35String& g35String)
  : LightProgram(g35String)
  , m_G35String(g35String)
{
    DebugPrintf("Test\n");

    delay_default_ = 5000;
}

bool Test::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    DebugPrintf("Initializing...\n");

    LightProgram::Initialize(pattern, option, delay);

    return true;
}

void Test::Update(pattern_t pattern, option_t option, delay_t delay)
{
    DebugPrintf("Updating...\n");
}

void Test::Kick(void)
{
    DebugPrintf("Kicking...\n");
}

uint32_t Test::Do()
{
    DebugPrintf("Do...\n");
    m_G35String.do_test_patterns();
    return delay_;
}


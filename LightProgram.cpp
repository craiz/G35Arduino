
#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM
#define ENABLE_DEBUG 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <LightProgram.h>

LightProgram::LightProgram(G35& g35)
  : g35_(g35),
    light_count_(g35.get_light_count()),
    pattern_(PATTERN_DEFAULT),
    option_(OPTION_DEFAULT),
    delay_(DELAY_DEFAULT),
    pattern_count_(0),
    option_default_(0),
    delay_default_(g35.get_bulb_frame()),
    waiting_(false)
{
}

LightProgram::~LightProgram()
{
}

// Return the current loop delay.
delay_t LightProgram::GetDelay()
{
    return delay_;
}


// Default implementation initializes settings to default values.
bool LightProgram::Initialize(pattern_t pattern, uint8_t option, delay_t delay)
{
    // Setup pattern
    pattern_ = pattern;
    if ((pattern_ == PATTERN_DEFAULT) && (pattern_count_ > 0))
    {
        // Randomize pattern
        pattern_ = rand() % pattern_count_;
    }

    // Setup delay
    delay_ = delay;
    if (delay_ == DELAY_DEFAULT)
    {
        delay_ = delay_default_;
    }

    // Setup option
    option_ = option;
    if (option_ == OPTION_DEFAULT)
    {
        option_ = option_default_;
    }

    return true;
}

// Default implementation does nothing.
uint32_t LightProgram::Do()
{
    return delay_;
}

// Default implementation updates settings.
void LightProgram::Update(pattern_t pattern, uint8_t option, delay_t delay)
{
    LightProgram::Initialize(pattern, option, delay);
}

void LightProgram::Kick()
{
    waiting_ = false;
}

bool LightProgram::IsWaiting()
{
    return waiting_;
}


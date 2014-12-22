/*
  This light program creates an effect of randomly blinking eyes.
  It is designed to run on a customized light string where each bulb
  is attached to a prop which looks like a set of eyes.
*/

#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_SPOOKY_EYES
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <SpookyEyes.h>

#define EYE_SIZE            1
#define NEW_EYE_TIME_BASE   1000

#define EYE_COUNT (light_count_ / EYE_SIZE)

SpookyEyes::SpookyEyes(G35& g35)
  : LightProgram(g35)
  , active_eye_count_(0)
  , next_eye_time_(0)
  , eyes_(NULL)
{
    DebugPrintf("SpookyEyes\n");
}

SpookyEyes::~SpookyEyes()
{
    if (eyes_)
    {
        free(eyes_);
    }
}

bool SpookyEyes::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    LightProgram::Initialize(pattern, option, delay);

    g35_.fill_color(0, light_count_, G35::MAX_INTENSITY, COLOR_BLACK);

    eyes_ = static_cast<Eye*>(malloc(EYE_COUNT * sizeof(Eye)));
    if (!eyes_)
    {
        DebugPrintf("Failed to allocate Eyes\n");
        return false;
    }
    for (int i = 0; i < EYE_COUNT; i++)
    {
        eyes_[i].Initialize();
    }

    // Randomly distribute the position of each eye.
    // This will allow for eye to appear to randomly become active rather than
    // linearly across the light string.
    light_count_t next_eye = 0;
    for (light_count_t position = 0; position < light_count_; position += EYE_SIZE)
    {        
        // Find an eye which does not already have a position.
        do
        {
            next_eye = rand() % EYE_COUNT;
        }
        while (eyes_[next_eye].get_position() != INVALID_POSITION);
        
        eyes_[next_eye].set_position(position);
        eyes_[next_eye].set_size(EYE_SIZE);
    }
    return true;
}

void SpookyEyes::Update(pattern_t pattern, option_t option, delay_t newDelay)
{
    if (SpookyEyes::ANGRY)
    {
        // Become Angry
        for (int i = 0; i < active_eye_count_; ++i)
        {
            eyes_[i].set_color(EYE_COLOR_WHITE);
            eyes_[i].set_state(EYE_STATE_STARING);
            eyes_[i].Do(g35_);
        }
        delay(25);

        for (int i = 0; i < active_eye_count_; ++i)
        {
            eyes_[i].set_color(EYE_COLOR_RED);
            eyes_[i].set_state(EYE_STATE_STARING);
        }        
    }
    else
    {
        // No longer angry
        for (int i = 0; i < active_eye_count_; ++i)
        {
            eyes_[i].set_state(EYE_STATE_SLEEPY);
        }
    }
}

uint32_t SpookyEyes::Do()
{
    // Let all actives eyes do some work
    for (int i = 0; i < active_eye_count_; ++i)
    {
        eyes_[i].Do(g35_);
    }

    // Activate another eye if it is time
    if ((active_eye_count_ < EYE_COUNT) && (millis() > next_eye_time_))
    {
        active_eye_count_++;
        next_eye_time_ = millis() + NEW_EYE_TIME_BASE + (rand() % NEW_EYE_TIME_BASE);
    }
    return delay_;
}

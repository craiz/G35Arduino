
#include <Eye.h>


#define BLINK_TIME_BASE     100
#define BLINK_TIME_RANDOM   200

#define WATCH_TIME_BASE     10000
#define WATCH_TIME_RANDOM   25000

#define SLEEP_TIME_BASE     1000
#define SLEEP_TIME_RANDOM   6000

#define SLEEPY_BLINK_BASE   3
#define SLEEPY_BLINK_RANDOM 10

#define DIMMING_DELAY       5


EYE_COLOR Eye::s_next_color = EYE_COLOR_ORANGE;

Eye::Eye()
{
    Initialize();
}

color_t Eye::get_color()
{
    switch (color_ % EYE_COLOR_COUNT)
    {
        case EYE_COLOR_ORANGE:      return COLOR_ORANGE;
        case EYE_COLOR_RED:         return COLOR_RED;
        case EYE_COLOR_BLUE:        return COLOR_BLUE;
        case EYE_COLOR_INDIGO:      return COLOR_INDIGO;
        case EYE_COLOR_GREEN:       return COLOR_GREEN;
        case EYE_COLOR_WHITE:       return COLOR_WHITE;
        case EYE_COLOR_PALE_ORANGE: return COLOR_PALE_ORANGE;
        case EYE_COLOR_VIOLET:      return COLOR_VIOLET;
        case EYE_COLOR_GREEN_NEON:  return COLOR_GREEN_NEON;
        case EYE_COLOR_YELLOW:      return COLOR_YELLOW;
        case EYE_COLOR_PURPLE:      return COLOR_PURPLE;
    }
}

void Eye::Initialize()
{
    color_ = EYE_COLOR_ORANGE;
    position_ = INVALID_POSITION;
    size_ = DEFAULT_EYE_SIZE;
    blink_count_ = 0;
    next_state_time_ = 0;
    next_state_ = EYE_STATE_INIT;
    intensity_ = G35::MAX_INTENSITY;
}

light_count_t Eye::get_position()
{
    return position_;
}

void Eye::set_position(light_count_t value)
{
    position_ = value;
}

void Eye::set_color(EYE_COLOR value)
{
    color_ = value;
}

void Eye::set_size(uint8_t value)
{
    size_ = value;
}

void Eye::set_state(EYE_STATE value)
{
    next_state_ = value;
    next_state_time_ = millis();
}

void Eye::Do(G35& g35)
{
    uint32_t now = millis();
    if (next_state_time_ < now)
    {
        switch (next_state_)
        {
            case EYE_STATE_INIT:
            {
                // Grab the next color and increment the shared index so the
                // next eye doesn't get the same color.
                color_ = s_next_color;
                s_next_color = (EYE_COLOR)((s_next_color + 1) % EYE_COLOR_COUNT);

                blink_count_ = SLEEPY_BLINK_BASE + (rand() % SLEEPY_BLINK_RANDOM);
                next_state_ = EYE_STATE_WAKING;
                break;
            }

            case EYE_STATE_WAKING:
            {
                if (intensity_ < G35::MAX_INTENSITY)
                {
                    intensity_++;
                    g35.fill_color(position_, size_, intensity_, get_color());
                }
                else
                {
                    next_state_ = EYE_STATE_WATCHING;
                }
                next_state_time_ = now + DIMMING_DELAY;
                break;
            }

            case EYE_STATE_WATCHING:
            {
                g35.fill_color(position_, size_, intensity_, get_color());
                next_state_time_ = now + WATCH_TIME_BASE + (rand() % WATCH_TIME_RANDOM);

                // Next we will be blinking or sleeping
                if (blink_count_ == 0)
                {
                    next_state_ = EYE_STATE_SLEEPY;
                }
                else
                {
                    next_state_ = EYE_STATE_BLINKING;
                }
                break;
            }

            case EYE_STATE_BLINKING:
            {
                blink_count_--;
                g35.fill_color(position_, size_, intensity_, COLOR_BLACK);
                next_state_time_ = now + BLINK_TIME_BASE + (rand() % BLINK_TIME_RANDOM);
                next_state_ = EYE_STATE_WATCHING;
                break;
            }

            case EYE_STATE_SLEEPY:
            {
                if (intensity_ > 0)
                {
                    intensity_--;
                    g35.fill_color(position_, size_, intensity_, get_color());
                }
                else
                {
                    next_state_ = EYE_STATE_SLEEPING;
                }
                next_state_time_ = now + DIMMING_DELAY;
                break;
            }

            case EYE_STATE_SLEEPING:
            {
                g35.fill_color(position_, size_, intensity_, COLOR_BLACK); 
                next_state_time_ = now + SLEEP_TIME_BASE + (rand() % SLEEP_TIME_RANDOM);
                next_state_ = EYE_STATE_INIT;
                break;
            }

            case EYE_STATE_STARING:
            {
                intensity_ = G35::MAX_INTENSITY;
                g35.fill_color(position_, size_, intensity_, get_color());
                break;
            }
        }
    }
}



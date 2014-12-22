#ifndef INCLUDE_G35_EYE_H
#define INCLUDE_G35_EYE_H

#include <G35.h>


#define INVALID_POSITION 255
#define DEFAULT_EYE_SIZE 2

typedef enum
{
    EYE_STATE_INIT,
    EYE_STATE_WAKING,
    EYE_STATE_WATCHING,
    EYE_STATE_BLINKING,
    EYE_STATE_SLEEPY,
    EYE_STATE_SLEEPING,
    EYE_STATE_STARING,

    EYE_STATE_COUNT // not a valid state
} EYE_STATE;

typedef enum
{
    EYE_COLOR_ORANGE,
    EYE_COLOR_RED,
    EYE_COLOR_BLUE,
    EYE_COLOR_INDIGO,
    EYE_COLOR_GREEN,
    EYE_COLOR_WHITE,
    EYE_COLOR_PALE_ORANGE,
    EYE_COLOR_VIOLET,
    EYE_COLOR_GREEN_NEON,
    EYE_COLOR_YELLOW,
    EYE_COLOR_PURPLE,

    EYE_COLOR_COUNT // not a valid color
} EYE_COLOR;


class Eye
{
public:
    Eye();

    void Initialize();

    light_count_t get_position();
    void set_position(light_count_t value);
    void set_color(EYE_COLOR value);
    void set_size(uint8_t value);
    void set_state(EYE_STATE value);

    void Do(G35& g35);



 private:

    color_t get_color();

    static EYE_COLOR s_next_color;

    EYE_COLOR color_;
    light_count_t position_;
    uint8_t blink_count_;
    uint32_t next_state_time_;
    uint8_t size_;
    uint8_t next_state_;
    uint8_t intensity_;
};

#endif // INCLUDE_G35_EYE_H

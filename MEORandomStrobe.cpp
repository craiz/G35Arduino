/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz

  See README for complete attributions.
*/

#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_MEORANDOMSTROBE
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <MEORandomStrobe.h>
#include <RainbowUtils.h>


#define COLOR_WHEEL_SIZE 48

MEORandomStrobe::MEORandomStrobe(G35& g35)
  : LightProgram(g35),
    preFill_(true),
    preFillBulb_(0),
    strobe_(true),
    wait_(25),
    noAtATime_(1),
    colorMain_(COLOR(0,0,4)),
    colorFlash_(COLOR_WHITE),
    rainbowFlash_(false),
    rainbowMain_(false),
    rainbowFrame_(false),
    step_(0),
    myBulb_(0),
    mySequence_(NULL)
{
    DebugPrintf("MEORandomStrobe\n");

    pattern_count_ = RANDOM_STROBE_PATTERN_COUNT;
}

MEORandomStrobe::~MEORandomStrobe()
{
    free(mySequence_);
}

bool MEORandomStrobe::Initialize(pattern_t pattern, uint8_t option, delay_t delay)
{
    DebugPrintf("Initializing...\n");

    Update(pattern, option, delay);

    // Allocate a buffer to hold the shuffled bulbs
    mySequence_ = static_cast<uint8_t*>(malloc(light_count_ * sizeof(light_count_t)));
    if (mySequence_ == NULL)
    {
        return false;
    }

    if (IS_RANDOM(option_))
    {
        // Random
        RandomizeStrobe();
    }
    else
    {
        // Fixed order
        for (light_count_t i = 0; i < light_count_; i++)
        {
            mySequence_[i] = i;
        }
    }

    return true;
}

void MEORandomStrobe::Update(pattern_t pattern, uint8_t option, delay_t delay)
{
    DebugPrintf("Updating...\n");

    // Handle default update
    LightProgram::Update(pattern, option, delay);

    if (!IS_FILL_IMMEDIATE(option_))
    {
        if (IS_FORWARD(option_))
        {
            preFillBulb_ = 0;
        }
        else
        {
            preFillBulb_ = light_count_;
        }
    }

    // option bits 5 - 7 controls number of strobes at a time.
    noAtATime_ = (option_ >> 4) & 7;
    if (!noAtATime_)
    {
        noAtATime_ = 1;
    }

    // option bit 8 allows disabling prefill (0=prefill (default), 1 = no prefill)
    preFill_ = !(option_ & OPTION_BIT_8);
}

void MEORandomStrobe::RandomizeStrobe()
{
    DebugPrintf("Randomizing strobe pattern\n");
    
    light_count_t hits = 0;
    light_count_t target;
    memset(mySequence_, light_count_, light_count_);
    while (hits < light_count_)
    {
        target = rand() % light_count_;
        if (mySequence_[target] == light_count_)
        {
            mySequence_[target] = hits;
            hits++;
        }
    }
}

uint32_t MEORandomStrobe::Do()
{
    switch (pattern_)
    {
    default:
    case RANDOM_STROBE_PATTERN_BLACK_WHITE: // Black background, white strobe
        rainbowMain_ = false;
        rainbowFlash_ = false;
        rainbowFrame_ = false;
        colorMain_ = COLOR_BLACK;
        colorFlash_ = COLOR_WHITE;
        break;
    case RANDOM_STROBE_PATTERN_BLUE_WHITE: // Blue background, white strobe
        rainbowMain_ = false;
        rainbowFlash_ = false;
        rainbowFrame_ = false;
        colorMain_ = COLOR(0,0,4); // dim blue for better contrast
        colorFlash_ = COLOR_WHITE;
        break;
    case RANDOM_STROBE_PATTERN_RED_WHITE: // Red background, white strobe
        rainbowMain_ = false;
        rainbowFlash_ = false;
        rainbowFrame_ = false;
        colorMain_ = COLOR(4,0,0); // dim red for better contrast
        colorFlash_ = COLOR_WHITE;
        break;
    case RANDOM_STROBE_PATTERN_GREEN_WHITE: // Green background, white strobe
        rainbowMain_ = false;
        rainbowFlash_ = false;
        rainbowFrame_ = false;
        colorMain_ = COLOR(0,4,0); // dim green for better contrast
        colorFlash_ = COLOR_WHITE;
        break;
    case RANDOM_STROBE_PATTERN_BLACK_RAINBOW_FULL:  // Black background, rainbow strobe (all bulbs before color increment)
        rainbowMain_ = false;
        rainbowFlash_ = true;
        rainbowFrame_ = true;
        colorMain_ = COLOR_BLACK;
        break;
    case RANDOM_STROBE_PATTERN_BLACK_RAINBOW:  // Black background, rainbow strobe
        rainbowMain_ = false;
        rainbowFlash_ = true;
        rainbowFrame_ = false;
        colorMain_ = COLOR_BLACK;
        break;
    case RANDOM_STROBE_PATTERN_RAINBOW_WHITE_FULL:  // Rainbow background, white strobe (all bulbs before color increment)
        rainbowMain_ = true;
        rainbowFlash_ = false;
        rainbowFrame_ = true;
        colorFlash_ = COLOR_WHITE;
        break;
    case RANDOM_STROBE_PATTERN_RAINBOW_WHITE:  // Rainbow background, white strobe
        rainbowMain_ = true;
        rainbowFlash_ = false;
        rainbowFrame_ = false;
        colorFlash_ = COLOR_WHITE;
        break;
    case RANDOM_STROBE_PATTERN_RAINBOW_RAINBOW_FULL:  // Rainbow background, rainbow strobe (all bulbs before color increment)
        rainbowMain_ = true;
        rainbowFlash_ = true;
        rainbowFrame_ = true;
        break;
    case RANDOM_STROBE_PATTERN_RAINBOW:  // Rainbow random transition to new color. (no strobe)
        rainbowMain_ = true;
        rainbowFlash_ = true;
        rainbowFrame_ = true;
        strobe_ = false;
        break;
    case RANDOM_STROBE_PATTERN_YELLOW_WHITE: // Yellow background, white strobe
        rainbowMain_ = false;
        rainbowFlash_ = false;
        rainbowFrame_ = false;
        colorMain_ = COLOR_YELLOW;
        colorFlash_ = COLOR_WHITE;
    }

    // pre-fill with background colour if flag set, and first step in
    if (preFill_)
    {
        if (IS_FILL_IMMEDIATE(option_))
        {
            // Set all bulbs at once.
            preFill_ = false;
            if (rainbowMain_)
            {
                for (light_count_t i = 0; i < light_count_; i++)
                {
                    g35_.set_color(i, G35::MAX_INTENSITY, GetWheelColor((step_ + COLOR_WHEEL_SIZE / 2) % COLOR_WHEEL_SIZE));
                    step_++;
                }
            }
            else
            {
                g35_.fill_color(0, light_count_, G35::MAX_INTENSITY, colorMain_);
            }
        }
        else
        {
            // Fill background color incrementally
            if (IS_FORWARD(option_))
            {
                // Forward
                if (preFillBulb_ >= light_count_)
                {
                    preFill_ = false;
                }
                else
                {
                    if (rainbowMain_)
                    {
                        g35_.set_color(preFillBulb_, G35::MAX_INTENSITY, GetWheelColor((step_ + COLOR_WHEEL_SIZE / 2) % COLOR_WHEEL_SIZE));
                    }
                    else
                    {
                        g35_.set_color(preFillBulb_, G35::MAX_INTENSITY, colorMain_);
                    }
                    preFillBulb_++;
                    step_++;
                    return g35_.get_bulb_frame();
                }
            }
            else
            {
                // Backward
                if (preFillBulb_ == 0)
                {
                    preFill_ = false;
                }
                else
                {
                    if (rainbowMain_)
                    {
                        g35_.set_color(preFillBulb_ - 1, G35::MAX_INTENSITY, GetWheelColor((step_ + COLOR_WHEEL_SIZE / 2) % COLOR_WHEEL_SIZE));
                    }
                    else
                    {
                        g35_.set_color(preFillBulb_- 1, G35::MAX_INTENSITY, colorMain_);
                    }
                    preFillBulb_--;
                    step_++;
                    return g35_.get_bulb_frame();
                }
            }
        }
    }

    // turn on (set to colorFlash) and off (set to colorMain) the random bulbs
    int simultan = 0;
    do
    {
        if (rainbowFlash_)
        {
            g35_.set_color(mySequence_[myBulb_], G35::MAX_INTENSITY, GetWheelColor(step_ % COLOR_WHEEL_SIZE));
        }
        else
        {
            g35_.set_color(mySequence_[myBulb_], G35::MAX_INTENSITY, colorFlash_);
        }

        myBulb_++;
        simultan++;
    }
    while ((simultan < noAtATime_) && (myBulb_ < light_count_));
    delay(wait_);

    //whether to keep the bulbs on or turn off
    if (strobe_) 
    {
        myBulb_ = myBulb_ - noAtATime_; //put back to where was before last do loop
        simultan = 0;
        do
        {
            if (rainbowMain_)
            {
                g35_.set_color(mySequence_[myBulb_], G35::MAX_INTENSITY, GetWheelColor((step_ + COLOR_WHEEL_SIZE / 2) % COLOR_WHEEL_SIZE));
            }
            else
            {
                g35_.set_color(mySequence_[myBulb_], G35::MAX_INTENSITY, colorMain_);
            }
            myBulb_++;
            simultan++;
        }
        while ((simultan < noAtATime_) && (myBulb_ < light_count_));
    }

    if (rainbowFrame_)
    {
        // change colour each frame - i.e. after all bulbs have been flashed
        if (myBulb_ >= light_count_)
        {
            myBulb_ = 0;
            step_++;
            if (step_ == COLOR_WHEEL_SIZE)
            {
                step_ = 0;
            }
        }
    }
    else
    {
        // change colour after each individual flash
        step_++;
        if (step_ == COLOR_WHEEL_SIZE)
        {
            step_ = 0;
        }
        if (myBulb_ >= light_count_)
        {
            myBulb_ = 0;
        }
    }

    // All bulbs have been strobed, check for wait and randomization
    if (myBulb_ == 0)
    {
        if (IS_RANDOM(option_))
        {
            RandomizeStrobe();
        }

        if (IS_WAIT(option_))
        {
            DebugPrintf("Waiting...\n");
            waiting_ = true;
            return 0;
        }
    }

    // Choose a random or fixed delay.
    if (IS_RANDOM(option_))
    {
        return rand() % delay_;
    }
    else
    {
        return delay_;
    }
}

/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2012 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.
  Programs referenced in MEOPrograms by Mark Ortiz <github.com/MarkEMarkEMark>.
  Portions adapted from Adafruit.

  See README for complete attributions.
*/

#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_RAINBOW
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <Rainbow.h>
#include <RainbowUtils.h>

#define PATTERN_COUNT (12)

Rainbow::Rainbow(G35& g35)
  : LightProgram(g35)
  , color_position_(0)
  , active_bulb_count_(1)
{
    DebugPrintf("Rainbow\n");

    pattern_count_ = PATTERN_COUNT;
    option_default_ = 0x10;
}

bool Rainbow::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    LightProgram::Initialize(pattern, option, delay);

    // Decide if all lights will immediately be controlled or if they will be slowly picked up.
    if (IS_FILL_IMMEDIATE(option_))
    {
        active_bulb_count_ = g35_.get_light_count();
    }

    // Set the initial step at the beginning or end of wheel/line.
    switch (pattern_)
    {
    case 0:
    case 4:
    case 8:
        palette_size_ = 48;
        break;
    default:
        palette_size_ = 32;
        break;
    }
    if (IS_FORWARD(option_))
    {
        // forward
        color_position_ = palette_size_;
    }
    else
    {
        // backward
        color_position_ = 0;
    }

    // Set the color increment
    color_increment_ = option_ >> 4;
    if ((color_increment_ == 0) || (color_increment_ % 2 > 0) || (color_increment_ > 8))
    {
        DebugPrintf("Invalid increment!\n");
        color_increment_ = 1;
    }

    return true;
}

uint32_t Rainbow::Do()
{
    // Update the color of each bulb.
    if (IS_FORWARD(option_))
    {
        // forward
        for(light_count_t bulb = active_bulb_count_; bulb > 0; bulb--)
        {
            SetBulb(bulb - 1);
        }
    }
    else
    {
        // backward
        for (light_count_t bulb = 0; bulb < active_bulb_count_; bulb++)
        {
            SetBulb(bulb);
        }
    }

    // Advance to the next color step.  Reset the current step at end or beginning of wheel/line.
    if (IS_FORWARD(option_))
    {
        // forward
        color_position_ -= color_increment_;
        if (color_position_ <= 0)
        {
            color_position_ = palette_size_ + color_position_;
        }
    }
    else
    {
        // backward
        color_position_ += color_increment_;
        if (color_position_ >= palette_size_)
        {
            color_position_ = color_position_ - palette_size_;
        }
    }

    // Increase the number of lights currently controlled by this program until
    // all lights are used.
    if (active_bulb_count_ < g35_.get_light_count())
    {
        active_bulb_count_++;
    }
    else if (IS_WAIT(option_))
    {
        DebugPrintf("Waiting...\n");
        waiting_ = true;
        return 0;
    }

    return delay_;
}
    

void Rainbow::SetBulb(light_count_t bulb)
{
    switch (pattern_)
    {
    case 0: // All bulbs full color wheel
        g35_.set_color(bulb, G35::MAX_INTENSITY, GetWheelColor(color_position_ % 48));
        break;
    case 1: // All bulbs red/green
        g35_.set_color(bulb, G35::MAX_INTENSITY, GetLineRGColor(color_position_ % 32));
        break;
    case 2: // All bulbs gree/blue
        g35_.set_color(bulb, G35::MAX_INTENSITY, GetLineGBColor(color_position_ % 32));
        break;
    case 3: // All bulbs blue/red
        g35_.set_color(bulb, G35::MAX_INTENSITY, GetLineBRColor(color_position_ % 32));
        break;

    case 4: // Chase full color wheel
        g35_.set_color(bulb, G35::MAX_INTENSITY, GetWheelColor((bulb + color_position_) % 48));
        break;
    case 5: // Chase red/green
        g35_.set_color(bulb, G35::MAX_INTENSITY, GetLineRGColor((bulb + color_position_) % 32));
        break;
    case 6: // Chase green/blue
        g35_.set_color(bulb, G35::MAX_INTENSITY, GetLineGBColor((bulb + color_position_) % 32));
        break;
    case 7: // Chase blue/red
        g35_.set_color(bulb, G35::MAX_INTENSITY, GetLineBRColor((bulb + color_position_) % 32));
        break;

    case 8: // Chase full color wheel
        g35_.set_color(bulb, G35::MAX_INTENSITY, GetWheelColor(((bulb * 48 / light_count_) + color_position_) % 48));
        break;
    case 9: // Chase red/green
        g35_.set_color(bulb, G35::MAX_INTENSITY, GetLineRGColor(((bulb * 32 / light_count_) + color_position_) % 32));
        break;
    case 10: // Chase green/blue
        g35_.set_color(bulb, G35::MAX_INTENSITY, GetLineGBColor(((bulb * 32 / light_count_) + color_position_) % 32));
        break;
    case 11: // Chase blue/red
        g35_.set_color(bulb, G35::MAX_INTENSITY, GetLineBRColor(((bulb * 32 / light_count_) + color_position_) % 32));
        break;
    }
}

void Rainbow::Update(pattern_t pattern, option_t option, delay_t delay)
{
    // This program doesn't allow the pattern to be updated.
    // Use the current pattern in the update.
    LightProgram::Update(pattern_, option, delay);

    // Set the color increment
    color_increment_ = option_ >> 4;
    if ((color_increment_ == 0) || (color_increment_ % 2 > 0) || (color_increment_ > 8))
    {
        DebugPrintf("Invalid increment!\n");
        color_increment_ = 1;
    }
}


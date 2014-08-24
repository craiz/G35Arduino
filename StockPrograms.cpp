/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  See README for complete attributions.
*/

#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_STOCK
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <StockPrograms.h>
#include <ColorUtils.h>

SingleColorProgram::SingleColorProgram(G35& g35)
    : LightProgram(g35)
{
}

bool SingleColorProgram::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    LightProgram::Initialize(pattern, option, delay);

    DecodeColorInfo(pattern_, &m_colorInfo);
    if (IS_RANDOM(option_))
    {
        m_colorInfo.index = NO_EXCLUDE;
    }
    SetupColor(false);
    return true;
}

void SingleColorProgram::Update(pattern_t pattern, option_t option, delay_t delay)
{
    Initialize(pattern, option, delay);
}

void SingleColorProgram::SetupColor(bool increment)
{
    if (IS_RANDOM(option_))
    {
        m_colorInfo.index = GetRandomPaleteColor(m_colorInfo.palete, m_colorInfo.index, NO_EXCLUDE);
    }
    else if (increment)
    {
        m_colorInfo.index = (m_colorInfo.index + 1) % GetPaleteMax(m_colorInfo.palete);
    }
    m_color = GetPaleteColor(&m_colorInfo);
}

SteadyWhite::SteadyWhite(G35& g35)
  : LightProgram(g35),
    intensity_(0)
{
    DebugPrintf("SteadyWhite\n");
}

bool SteadyWhite::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    LightProgram::Initialize(pattern, option, delay);

    g35_.fill_color(0, light_count_, 0, COLOR_WHITE);
    return true;
}

uint32_t SteadyWhite::Do()
{
    if (intensity_ <= G35::MAX_INTENSITY)
    {
        g35_.broadcast_intensity(intensity_++);
    }
    return delay_;
}

SteadyMulti::SteadyMulti(G35& g35)
  : LightProgram(g35),
    intensity_(0)
{
    DebugPrintf("SteadyMulti\n");
}

bool SteadyMulti::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    LightProgram::Initialize(pattern, option, delay);

    color_t color;
    for (light_count_t i = 0; i < light_count_; i++)
    {
        switch(i % 5)
        {
        case 0:
            color = COLOR_RED;
            break;
        case 1:
            color = COLOR_GREEN;
            break;
        case 2:
            color = COLOR_ORANGE;
            break;
        case 3:
            color = COLOR_BLUE;
            break;
        case 4:
            color = COLOR_YELLOW;
            break;
        }
        g35_.set_color(i, 0, color);
    }
    return true;
}

uint32_t SteadyMulti::Do()
{
    if (intensity_ <= G35::MAX_INTENSITY)
    {
        g35_.broadcast_intensity(intensity_++);
    }
    return delay_;
}

CrossOverWave::CrossOverWave(G35& g35)
  : LightProgram(g35),
    x_(light_count_)
{
    DebugPrintf("CrossOverWave\n");
}

uint32_t CrossOverWave::Do()
{
    if (x_ == light_count_)
    {
        x_ = 0;
        color_a_ = 0;
        color_b_ = 0;
        while (color_a_ == color_b_)
        {
            color_a_ = G35::max_color(rand());
            color_b_ = G35::max_color(rand());
        }
    }
    g35_.set_color(x_, G35::MAX_INTENSITY, color_a_);
    g35_.set_color(g35_.get_last_light() - x_, G35::MAX_INTENSITY, color_b_);
    ++x_;

    if ((x_ == light_count_) && IS_WAIT(option_))
    {
        waiting_ = true;
        DebugPrintf("Waiting...\n");
    }
    
    return delay_;
}

// ForwardWave
//
// Options supported: Wait, Random
// If Random is true, the colors are randomly chosen.
// If Random is false, the color is specified by pattern.
ForwardWave::ForwardWave(G35& g35)
  : SingleColorProgram(g35),
    x_(0)
{
    DebugPrintf("ForwardWave\n");
}

uint32_t ForwardWave::Do()
{
    g35_.set_color(x_, G35::MAX_INTENSITY, m_color);
    ++x_;

    if (x_ == light_count_)
    {
        x_ = 0;
        SetupColor(true);
    
        if (IS_WAIT(option_))
        {
            waiting_ = true;
            DebugPrintf("Waiting...\n");
        }
    }

    return delay_;
}

ChasingRainbow::ChasingRainbow(G35& g35)
  : LightProgram(g35),
    count_(1),
    sequence_(0)
{
    DebugPrintf("ChasingRainbow\n");
}

uint32_t ChasingRainbow::Do()
{
    g35_.fill_sequence(0, count_, sequence_, 1, G35::MAX_INTENSITY, G35::rainbow_color);
    if (count_ < light_count_)
    {
        ++count_;
    }
    else
    {
        ++sequence_;
    }
    return delay_;
}

// AlternateDirectionalWave
//
// Options supported: Wait, Random
// If Random is true, the colors are randomly chosen.
// If Random is false, the color is specified by pattern.
AlternateDirectionalWave::AlternateDirectionalWave(G35& g35)
  : SingleColorProgram(g35),
    x_(0),
    x_target_(light_count_),
    x_other_target_(-1),
    direction_(1)
{
    DebugPrintf("AlternateDirectionalWave\n");
}

uint32_t AlternateDirectionalWave::Do()
{
    g35_.set_color(x_, G35::MAX_INTENSITY, m_color);
    x_ += direction_;

    if (x_ == x_target_)
    {
        direction_ = -direction_;
        x_ += direction_;
        int16_t t = x_target_;
        x_target_ = x_other_target_;
        x_other_target_ = t;

        SetupColor(true);

        if (IS_WAIT(option_))
        {
            waiting_ = true;
            DebugPrintf("Waiting...\n");
        }
        
        return 1000;
    }
    return delay_;
}

// FadeInFadeOutSingleColors
//
// Options supported: Wait, Random
// If Random is true, the colors are randomly chosen.
// If Random is false, the color is specified by pattern.
FadeInFadeOutSingleColors::FadeInFadeOutSingleColors(G35& g35)
  : SingleColorProgram(g35),
    intensity_(-1),
    d_intensity_(1)
{
    DebugPrintf("FadeInFadeOutSingleColors\n");

    delay_default_ = 10;
}

uint32_t FadeInFadeOutSingleColors::Do()
{
    intensity_ += d_intensity_;

    if (intensity_ == 0)
    {
        // We are at minimul intensity, output a new color.
        g35_.fill_color(0, light_count_, intensity_, m_color);

        // Going up.
        d_intensity_ = 1;
    }
    else
    {
        // update intensity
        g35_.broadcast_intensity(intensity_);
    }

    if (intensity_ == G35::MAX_INTENSITY)
    {
        // Pick a new color.
        SetupColor(true);
    
        // If we at max intensity and the wait option is enabled, 
        // set the wait flag so we wait after this do.
        if (IS_WAIT(option_))
        {
            DebugPrintf("Waiting...\n");
            waiting_ = true;
        }

        // Going down.
        d_intensity_ = -1;
    }

    return delay_;
}

BidirectionalWave::BidirectionalWave(G35& g35)
  : LightProgram(g35),
    x_(g35_.get_halfway_point()),
    firstWave_(true)
{
    DebugPrintf("BidirectionalWave\n");
}

uint32_t BidirectionalWave::Do()
{
    // With 50 lights, we run into some edge cases because 50 isn't evenly
    // divisible by 4. It's a fairly crazy program to start with, so I'm
    // leaving it like this.
    if (x_ == g35_.get_halfway_point())
    {
        x_ = 0;
        do
        {
            color_a_ = G35::max_color(rand());
            color_b_ = G35::max_color(rand());
        }
        while (color_a_ == color_b_);
        do
        {
            color_c_ = G35::max_color(rand());
            color_d_ = G35::max_color(rand());
        }
        while (color_c_ == color_d_);

        if (IS_WAIT(option_) && !firstWave_)
        {
            DebugPrintf("Waiting...\n");
            waiting_ = true;
            return 0;
        }

        firstWave_ = false;
    }
    g35_.set_color(x_, G35::MAX_INTENSITY, color_a_);
    g35_.set_color(g35_.get_halfway_point() - 1 - x_, G35::MAX_INTENSITY, color_b_);
    g35_.set_color(g35_.get_halfway_point() + x_, G35::MAX_INTENSITY, color_c_);
    g35_.set_color(g35_.get_last_light() - x_, G35::MAX_INTENSITY, color_d_);
    ++x_;
    return delay_;
}

ChasingSolidColors::ChasingSolidColors(G35& g35)
  : LightProgram(g35),
    count_(1),
    sequence_(0)
{
    DebugPrintf("ChasingSolidColors\n");
}

uint32_t ChasingSolidColors::Do()
{
    g35_.fill_sequence(0, count_, sequence_, 5, G35::MAX_INTENSITY, G35::max_color);
    if (count_ < light_count_)
    {
        ++count_;
    }
    else
    {
        ++sequence_;
    }
    return delay_;
}

FadeInFadeOutMultiColors::FadeInFadeOutMultiColors(G35& g35)
  : LightProgram(g35),
    state_(0),
    intensity_(0)
{
    DebugPrintf("FadeInFadeOutMultiColors\n");

    delay_default_ = 10;
}

uint32_t FadeInFadeOutMultiColors::Do()
{
    switch (state_)
    {
        case 0:
            if (intensity_++ == 0)
            {
                // We mask off the last two bits so that the color segments are aligned
                // from scene to scene.
                g35_.fill_sequence(rand() & 0x7ffc, 4, 0, G35::max_color);
            }
            if (intensity_ == G35::MAX_INTENSITY)
            {
                if (IS_WAIT(option_))
                {
                    DebugPrintf("Waiting...\n");
                    waiting_ = true;
                }
                state_ = 1;
            }
            break;
        case 1:
            if (--intensity_ == 0)
            {
                state_ = 0;
            }
            break;
    }
     g35_.broadcast_intensity(intensity_);

    return delay_;
}

ChasingTwoColors::ChasingTwoColors(G35& g35)
  : LightProgram(g35),
    sequence_(0)
{
    DebugPrintf("ChasingTwoColors\n");

    delay_default_ = 500;
}

uint32_t ChasingTwoColors::Do()
{
    g35_.fill_sequence(sequence_, light_count_ / 2, G35::MAX_INTENSITY, G35::rainbow_color);
    sequence_ += light_count_ / 2;

    if (IS_WAIT(option_))
    {
        DebugPrintf("Waiting...\n");
        waiting_ = true;
    }
    
    return delay_;
}

RandomSparkling::RandomSparkling(G35& g35)
  : LightProgram(g35),
    state_(1)
{
    DebugPrintf("RandomSparkling\n");

    delay_default_ = 500;
}

uint32_t RandomSparkling::Do()
{
    if (state_++ > 1)
    {
        state_ = 0;
    }
    if (state_ == 0)
    {
        g35_.fill_random_max(0, light_count_, G35::MAX_INTENSITY);
        return delay_ * 2;
    }
    g35_.fill_color(0, light_count_, G35::MAX_INTENSITY, COLOR_BLACK);
    return delay_;
}

ChasingMultiColors::ChasingMultiColors(G35& g35)
  : LightProgram(g35),
    count_(1),
    sequence_(0)
{
    DebugPrintf("ChasingMultiColors\n");

    delay_default_ = g35_.get_bulb_frame() * 6;
}

uint32_t ChasingMultiColors::Do()
{
    g35_.fill_sequence(0, count_, sequence_, 1, G35::MAX_INTENSITY, G35::max_color);
    if (count_ < light_count_)
    {
        ++count_;
    }
    else
    {
        ++sequence_;
    }
    return delay_;
}

ChasingRedWhiteBlue::ChasingRedWhiteBlue(G35& g35)
  : LightProgram(g35),
    count_(1),
    sequence_(0)
{
  DebugPrintf("ChasingRedWhiteBlue\n");
}

uint32_t ChasingRedWhiteBlue::Do()
{
    g35_.fill_sequence(0, count_, sequence_, 3, G35::MAX_INTENSITY, red_white_blue);
    if (count_ < light_count_)
    {
        ++count_;
    }
    else
    {
        ++sequence_;
    }
    return delay_;
}

// static
color_t ChasingRedWhiteBlue::red_white_blue(sequence_t sequence)
{
    sequence = sequence % 3;
    if (sequence == 0)
    {
        return COLOR_RED;
    }
    if (sequence == 1)
    {
        return COLOR_WHITE;
    }
    return COLOR_BLUE;
}

ChasingRedWhiteGreen::ChasingRedWhiteGreen(G35& g35)
  : LightProgram(g35),
    count_(1),
    sequence_(0)
{
    DebugPrintf("ChasingRedWhiteGreen\n");
}

uint32_t ChasingRedWhiteGreen::Do()
{
    g35_.fill_sequence(0, count_, sequence_, 3, G35::MAX_INTENSITY, red_white_green);
    if (count_ < light_count_)
    {
        ++count_;
    }
    else
    {
        ++sequence_;
    }
    return delay_;
}

// static
color_t ChasingRedWhiteGreen::red_white_green(sequence_t sequence)
{
    sequence = sequence % 3;
    if (sequence == 0)
    {
        return COLOR_RED;
    }
    if (sequence == 1)
    {
        return COLOR_WHITE;
    }
    return COLOR_GREEN;
}

LightProgram* StockProgramGroup::CreateProgram(G35& lights, uint8_t program_index)
{
    switch (program_index % ProgramCount)
    {
        case 0: return new SteadyWhite(lights);
        case 1: return new SteadyMulti(lights);
        case 2: return new CrossOverWave(lights);
        case 3: return new ForwardWave(lights);
        case 4: return new ChasingRainbow(lights);
        case 5: return new AlternateDirectionalWave(lights);
        case 6: return new FadeInFadeOutSingleColors(lights);
        case 7: return new BidirectionalWave(lights);
        case 8: return new ChasingSolidColors(lights);
        case 9: return new FadeInFadeOutMultiColors(lights);
        case 10: return new ChasingTwoColors(lights);
        case 11: return new RandomSparkling(lights);
        case 12: return new ChasingMultiColors(lights);
        case 13: return new ChasingRedWhiteBlue(lights);
        case 14: return new ChasingRedWhiteGreen(lights);
    }

    // not reached
    return NULL;
}

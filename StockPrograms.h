/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_STOCK_PROGRAMS_H
#define INCLUDE_G35_STOCK_PROGRAMS_H

#include <LightProgram.h>
#include <ColorUtils.h>

// We don't count SteadyWhite because it's more of a mode than a program.
#define STOCK_PROGRAM_COUNT (12)

class SingleColorProgram : public LightProgram
{
public:
    SingleColorProgram(G35& g35);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    void Update(pattern_t pattern, option_t option, delay_t delay);


protected:
    void SetupColor(bool increment);

    COLOR_INFO m_colorInfo;

    color_t m_color;
};


class SteadyWhite : public LightProgram
{
public:
    SteadyWhite(G35& g35);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    uint32_t Do();

private:
    uint8_t intensity_;
};

class SteadyMulti : public LightProgram
{
public:
    SteadyMulti(G35& g35);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    uint32_t Do();

private:
    uint8_t intensity_;
};

class CrossOverWave : public LightProgram
{
public:
    CrossOverWave(G35& g35);
    uint32_t Do();

private:
    light_count_t x_;
    color_t color_a_;
    color_t color_b_;
};

class ForwardWave : public SingleColorProgram
{
public:
    ForwardWave(G35& g35);
    uint32_t Do();

private:

    light_count_t x_;
};

class ChasingRainbow : public LightProgram
{
public:
    ChasingRainbow(G35& g35);
    uint32_t Do();

private:
    light_count_t count_;
    sequence_t sequence_;
};

class AlternateDirectionalWave : public SingleColorProgram
{
public:
    AlternateDirectionalWave(G35& g35);
    uint32_t Do();

private:

    int16_t x_;
    int16_t x_target_;
    int16_t x_other_target_;
    int8_t direction_;
};

class FadeInFadeOutSingleColors : public SingleColorProgram
{
public:
    FadeInFadeOutSingleColors(G35& g35);
    uint32_t Do();

private:

    uint8_t intensity_;
    int8_t d_intensity_;
};

class BidirectionalWave : public LightProgram
{
public:
    BidirectionalWave(G35& g35);
    uint32_t Do();

private:
    uint8_t x_;
    color_t color_a_;
    color_t color_b_;
    color_t color_c_;
    color_t color_d_;
    bool firstWave_;
};

class ChasingSolidColors : public LightProgram
{
public:
    ChasingSolidColors(G35& g35);
    uint32_t Do();

private:
    light_count_t count_;
    sequence_t sequence_;
};

class FadeInFadeOutMultiColors : public LightProgram
{
public:
    FadeInFadeOutMultiColors(G35& g35);
    uint32_t Do();

private:
    uint8_t state_;
    uint8_t intensity_;
};

class ChasingTwoColors : public LightProgram
{
public:
    ChasingTwoColors(G35& g35);
    uint32_t Do();

private:
    sequence_t sequence_;
};

class RandomSparkling : public LightProgram
{
public:
    RandomSparkling(G35& g35);
    uint32_t Do();

private:
    uint8_t state_;
};

class ChasingMultiColors : public LightProgram
{
public:
    ChasingMultiColors(G35& g35);
    uint32_t Do();

private:
    light_count_t count_;
    sequence_t sequence_;
};

class ChasingRedWhiteBlue : public LightProgram
{
public:
    ChasingRedWhiteBlue(G35& g35);
    uint32_t Do();
    static color_t red_white_blue(sequence_t sequence);

 private:
    light_count_t count_;
    sequence_t sequence_;
};

class ChasingRedWhiteGreen : public LightProgram
{
public:
    ChasingRedWhiteGreen(G35& g35);
    uint32_t Do();
    static color_t red_white_green(sequence_t sequence);

 private:
    light_count_t count_;
    sequence_t sequence_;
};

class StockProgramGroup : public LightProgramGroup
{
public:
    enum { ProgramCount = 15 };

    virtual LightProgram* CreateProgram(G35& lights, uint8_t program_index);
};

#endif  // INCLUDE_G35_STOCK_PROGRAMS_H

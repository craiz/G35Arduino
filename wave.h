/*
 This program creates a wave effect by transitioning between colors.
 Full saturation colors are supported.

  By Paul Irwin
*/

#ifndef INCLUDE_G35_PROGRAMS_WAVE_H
#define INCLUDE_G35_PROGRAMS_WAVE_H

#include <LightProgram.h>
#include <ColorNodeCommands.h>
#include <WaveUtils.h>

// The parameters are tightly packed into the available space in the command buffer.
//
// pattern (8-bit)
// N N N N N N N N
// N = number of colors
//
// option (8-bit)
// I I I I 4 3 2 1
// I = increments (1-15, increments between colors)
// 4 = option 4
// 3 = option 3
// 2 = option 2
// 1 = option 1

// Number of colors 2 - 16 (8 bits)
// array of colors (0-7 color, 3 bits per color)
// array of holds (0-255, 8 bits per hold)
// increments 1 - 15 (4 bits)
// pixels per wave (0 = wave size, > 0 is fixed count but bounded to wave size and string size)
// pixel distribution (0 = even, > 0 is fixed spacing but bounded to even spacing)
// position span size (> 0) this is the number of bulbs to set for each wave position

// Pattern = Number of colors
// Option (high) = increments

// Example with 2 colors
// ProgramCommand (pattern = color count, option = increments)
// Pixels per wave
// Pixel Distribution
// Position span size
// Color 1
// Color 2
// Hold 1
// Hold 2


class Wave : public LightProgram
{
public:
    Wave(G35& g35, ProgramCommand *pCommand);
    ~Wave();
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    void Uninitialize();
    uint32_t Do();
    void Update(pattern_t pattern, option_t option, delay_t delay);

private:

    ProgramCommand *m_pCommand;
    light_count_t m_positionSpan;
    light_count_t count_;
};

#endif


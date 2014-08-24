/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_LIGHT_PROGRAMS_H
#define INCLUDE_G35_LIGHT_PROGRAMS_H

#include <G35.h>

#define PROGRAM_DEFAULT 0x00
#define PATTERN_DEFAULT 0xFF
#define DELAY_DEFAULT   0xFFFF
#define DURATION_NONE   0x00
#define OPTION_DEFAULT  0x00


#define OPTION_BIT_8            0x80
#define OPTION_BIT_7            0x40
#define OPTION_BIT_6            0x20
#define OPTION_BIT_5            0x10
#define OPTION_BIT_4            0x08
#define OPTION_BIT_3            0x04
#define OPTION_BIT_2            0x02
#define OPTION_BIT_1            0x01

#define OPTION_DIRECTION        OPTION_BIT_1
#define OPTION_FILL             OPTION_BIT_2
#define OPTION_RANDOM           OPTION_BIT_3
#define OPTION_WAIT             OPTION_BIT_4


// Helpful macros for setting option flags
#define PROGRAM_OPTION_FORWARD 0x00
#define PROGRAM_OPTION_BACKWARD 0x01

#define PROGRAM_OPTION_FIXED 0x04
#define PROGRAM_OPTION_RANDOM 0x00

#define PROGRAM_OPTION_IMMEDIATE 0x00
#define PROGRAM_OPTION_INCREMENTAL 0x02

#define PROGRAM_OPTION_WAIT 0x08
#define PROGRAM_OPTION_NO_WAIT 0x00

// The default option flags of 0x00:
//      Direction: Forward
//      Fill: Immediate
//      Random: True
//      Wait: False
#define PROGRAM_OPTION_DEFAULT OPTION_DEFAULT

// Helpful macros for checking option flags.

// The high 4 bits are used by several programs as a sub-pattern specifier.
// For example:
//      MEORandomStrobe: the number of simultaneous strobes.

// If option bit 1 is set, direction is backward, otherwise forward (default)
#define IS_FORWARD(__option)        !(__option & OPTION_DIRECTION)

// If option bit 2 is set, fill in bulbs incrementally, otherwise all bulbs immediately (default)
#define IS_FILL_IMMEDIATE(__option) !(__option & OPTION_FILL)

// If option bit 3 is set, not random, otherwise random (default)
#define IS_RANDOM(__option)         !(__option & OPTION_RANDOM)

// If option bit 4 is set, perform one program "cycle" then wait for update command before
// executing another "cycle", otherwise no waiting (default)
#define IS_WAIT(__option)           (__option & OPTION_WAIT)



// Fill mode.
typedef enum FILL_MODE
{
    FILL_MODE_ONE_DIRECTION = 0,
    FILL_MODE_BOTH_DIRECTIONS
};

// Wait mode.
typedef enum WAIT_MODE
{
    WAIT_MODE_PER_CYCLE = 0,
    WAIT_MODE_PER_ITEM
};


// Interface for light programs.
//
// A "light program" is what GE means when they say their lights include 14
// programs. An example is "Chasing Red, White, and Blue."
class LightProgram
{
public:
    LightProgram(G35& g35);
    virtual ~LightProgram();

    // All initiialization and memory allocations should be performed here.
    // Returns true/false indicating if the program was successfully initialized.
    virtual bool Initialize(pattern_t pattern, uint8_t option, delay_t delay);

    // Do a single slice of work. Returns the number of milliseconds before
    // this function should be called again.
    virtual uint32_t Do();

    // Update the parameters of the program.  This allows for changing the speed of a
    // pattern on the fly or more interesting options like changing the pattern or direction.
    virtual void Update(pattern_t pattern, uint8_t option, delay_t delay);

    // Return the current loop delay.
    virtual delay_t GetDelay();

    virtual void Kick();

    bool IsWaiting();

protected:
    G35& g35_;
    light_count_t light_count_;
    pattern_t pattern_;
    option_t option_;
    delay_t delay_;
    bool waiting_;

    // Settings defaults which can be overridden by sub-classes.
    uint8_t pattern_count_;
    uint8_t option_default_;
    delay_t delay_default_;
};

// A collection of LightProgram classes. Putting them here makes it much
// easier on app developers because they don't have to create a switch
// statement for every set of programs they're interested in including.
class LightProgramGroup
{
public:
    virtual LightProgram* CreateProgram(G35& lights, uint8_t program_index) = 0;
};

#endif  // INCLUDE_G35_LIGHT_PROGRAMS_H

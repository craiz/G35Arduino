/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <github.com/sowbug>.

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_PROGRAM_RUNNER_H
#define INCLUDE_G35_PROGRAM_RUNNER_H

#include <LightProgram.h>

// ProgramRunner manages a collection of LightPrograms.
//
// It gives the current program a slice of time to run, decides when it's
// time to switch to the next program, and asks the program_creator callback
// to give it the next program when it's time. In Arduino terms, it's what
// you want to call in your loop() method.
//
// SwitchProgram() and AdvanceProgram() allow the application to control
// when/how programs changed.  For example if you've implemented
// a remote control receiver.
class ProgramRunner
{
public:
    ProgramRunner(LightProgram* (*programCreator)(uint8_t programIndex), uint8_t programCount);

    void loop();
    void SwitchProgram(uint8_t programIndex, pattern_t pattern, option_t option, delay_t delay);
    void AdvanceProgram();
    void SetAutoAdvanceEnabled(bool enabled);
    void SetAutoAdvanceBounds(uint8_t minIndex, uint8_t maxIndex);
    void SetDuration(uint16_t programDurationSeconds);
    void UpdateProgram(uint8_t programIndex, pattern_t pattern, option_t option, delay_t delay);

    void Kick();

    uint32_t GetLastSwitchMillis();
    uint8_t GetProgramIndex();

private:

    bool SwitchProgramInternal(uint8_t programIndex, pattern_t pattern, option_t option, delay_t delay);

    bool m_autoAdvance;
    uint8_t m_autoAdvanceMinIndex;
    uint8_t m_autoAdvanceMaxIndex;
    uint8_t m_programCount;
    uint16_t m_programDurationSeconds;
    uint8_t m_programIndex;
    uint32_t m_lastSwitchMillis; // When last program switch occurred.
    uint32_t m_lastDoMillis; // When last program 'do' was run.
    uint32_t m_lastDoDelay;  // Requested delay of last program 'do'
    LightProgram* (*m_programCreator)(uint8_t programIndex);
    LightProgram* m_program;
};

#endif  // INCLUDE_G35_PROGRAM_RUNNER_H

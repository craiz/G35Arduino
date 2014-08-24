/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <github.com/sowbug>.

  See README for complete attributions.
*/

#include <DebugConfig.h>
#if DEBUG_PROGRAM_RUNNER
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <ProgramRunner.h>

ProgramRunner::ProgramRunner(LightProgram* (*programCreator)(uint8_t programIndex), uint8_t programCount)
  : m_programCount(programCount),
    m_autoAdvance(true),
    m_autoAdvanceMinIndex(0),
    m_autoAdvanceMaxIndex(programCount - 1),
    m_programDurationSeconds(30),
    m_programIndex(0),
    m_lastSwitchMillis(0),
    m_programCreator(programCreator),
    m_program(NULL),
    m_lastDoMillis(0),
    m_lastDoDelay(0)
{
    SwitchProgram(PROGRAM_DEFAULT, PATTERN_DEFAULT, OPTION_DEFAULT, DELAY_DEFAULT);
}

void ProgramRunner::loop()
{
    uint32_t now = millis();

    // Advance to the next program if needed.
    if (m_autoAdvance && (m_lastSwitchMillis + (m_programDurationSeconds * 1000) <= now))
    {
        AdvanceProgram();
    }

    // Do the next cycle of the program
    if (m_program)
    {
        if ((m_lastDoMillis + m_lastDoDelay) <= now)
        {
            m_lastDoMillis = now;
            if (!m_program->IsWaiting())
            {
                m_lastDoDelay = m_program->Do();
            }
        }
    }
}

void ProgramRunner::SwitchProgram(uint8_t programIndex, pattern_t pattern, option_t option, delay_t delay)
{
    if (programIndex < m_programCount)
    {
        if (!SwitchProgramInternal(programIndex, pattern, option, delay))
        {
            // Failed to switch to desired program, try default program 0.
            SwitchProgramInternal(PROGRAM_DEFAULT, PATTERN_DEFAULT, OPTION_DEFAULT, DELAY_DEFAULT);
        }
    }
    else
    {
        DebugPrintf("SwitchProgram: Index(%u) out of range!\n", programIndex);
    }
}

void ProgramRunner::AdvanceProgram()
{
    uint8_t newIndex = m_programIndex + 1;
    if (newIndex >= m_programCount || newIndex > m_autoAdvanceMaxIndex)
    {
        newIndex = m_autoAdvanceMinIndex;
    }

    SwitchProgram(newIndex, PATTERN_DEFAULT, OPTION_DEFAULT, DELAY_DEFAULT);
}

void ProgramRunner::SetAutoAdvanceEnabled(bool autoAdvance)
{
    m_autoAdvance = autoAdvance;
}

void ProgramRunner::SetAutoAdvanceBounds(uint8_t minIndex, uint8_t maxIndex)
{
    m_autoAdvanceMinIndex = minIndex;
    m_autoAdvanceMaxIndex = maxIndex;
}

void ProgramRunner::SetDuration(uint16_t programDurationSeconds)
{
    m_programDurationSeconds = programDurationSeconds;
}

void ProgramRunner::UpdateProgram(uint8_t programIndex, pattern_t pattern, option_t option, delay_t delay)
{
    if (!m_program)
    {
        DebugPrintf("Update requested, but no program is loaded!\n");
        return;
    }

    if (programIndex != m_programIndex)
    {
        DebugPrintf("Update requested for program index %u, but program index %u is loaded.\n", programIndex, m_programIndex);
        return;
    }

    DebugPrintf("Updating program index %u\n", m_programIndex);

    m_program->Update(pattern, option, delay);
    Kick();
}

bool ProgramRunner::SwitchProgramInternal(uint8_t programIndex, pattern_t pattern, option_t option, delay_t delay)
{
    DebugPrintf("Switching to program index %u\n", programIndex);

    uint32_t now = millis();
    m_lastSwitchMillis = now;
    m_lastDoMillis = 0;
    m_lastDoDelay = 0;

    if (m_program != NULL)
    {
        DebugPrintf("Deleting old program index %u\n", m_programIndex);
        delete m_program;
        m_program = NULL;
    }

    m_programIndex = programIndex;
    m_program = m_programCreator(m_programIndex);
    if (m_program)
    {
        DebugPrintf("Initializing program index %u\n", m_programIndex);
        if (m_program->Initialize(pattern, option, delay))
        {
            return true;
        }
        else
        {
            DebugPrintf("Failed to initialize program!\n");
            delete m_program;
            m_program = NULL;
            return false;
        }
    }
    else
    {
        DebugPrintf("Failed to create program!\n");
        return false;
    }  
}

uint32_t ProgramRunner::GetLastSwitchMillis()
{
    return m_lastSwitchMillis;
}

uint8_t ProgramRunner::GetProgramIndex()
{
    return m_programIndex;
}

void ProgramRunner::Kick()
{
    if (!m_program)
    {
        DebugPrintf("Kick requested, but no program is loaded!\n");
        return;
    }

    m_program->Kick();

    // Reset last delay to ensure that there is no residual delay.
    m_lastDoDelay = 0;
}

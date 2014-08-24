/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz
  and Adafruit

  See README for complete attributions.
*/

#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_MEOSWITCHOFF
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <MEOSwitchOff.h>

MEOSwitchOff::MEOSwitchOff(G35& g35)
  : LightProgram(g35)
  , m_Intensity(G35::MAX_INTENSITY)
{
    DebugPrintf("MEOSwitchOff\n");
}

uint32_t MEOSwitchOff::Do()
{
    switch (pattern_)
    {
    case 0: // Immediate Off
        g35_.broadcast_intensity(0);
        delay_ = 0xFFFF;
        break;
    case 1: // Soft Off
        if (m_Intensity > 0)
        {
            m_Intensity--;
            g35_.broadcast_intensity(m_Intensity);
        }
        break;
    }

    return delay_;
}
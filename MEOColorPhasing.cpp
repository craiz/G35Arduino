/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright � 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz
  and Adafruit

  See README for complete attributions.
*/

#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_MEOCOLORPHASING
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <MEOColorPhasing.h>

#define PI 3.14159265
#define PATTERN_COUNT 5

MEOColorPhasing::MEOColorPhasing(G35& g35)
  : LightProgram(g35),
    frequencyR_(0.06),
    frequencyG_(0.06),
    frequencyB_(0.06),
    phaseR_(0),
    phaseG_(2*PI/3),
    phaseB_(4*PI/3),
    center_(8),
    width_(7),
    fStep_(0),
    pStep_(0),
    fForward_(true),
    turn_(0)
{
    DebugPrintf("MEOColorPhasing\n");

    pattern_count_ = PATTERN_COUNT;
}

// neat rainbow phase 0, 2*PI/3, 4*PI/3 (120deg = 2PI/3, so 0, 120, 240)

uint32_t MEOColorPhasing::Do()
{
    switch (pattern_ % 5)
    {
    case 0:  //Wavey pastels
        phaseR_ = 0;
        phaseB_ = 2*PI/3;
        phaseG_ = 4*PI/3;
        frequencyR_ = float(fStep_) / 100.0;
        frequencyG_ = float(fStep_) / 100.0;
        frequencyB_ = float(fStep_) / 100.0;
        break;
    case 1: // subtly changing pastels
        phaseR_ = 0;
        phaseB_ = (2*PI/360) * pStep_;
        phaseG_ = (4*PI/360) * pStep_;
        frequencyR_ = 1.666;
        frequencyG_ = 2.666;
        frequencyB_ = 3.666;
        break;
    case 2: //White twinkle
        phaseR_ = pStep_;
        phaseB_ = pStep_;
        phaseG_ = pStep_;
        frequencyR_ = float(fStep_) / 100.0;
        frequencyG_ = float(fStep_) / 100.0;
        frequencyB_ = float(fStep_) / 100.0;
        break;
    case 3: //Evolving pastel wave
        switch (turn_ % 6)
        {
        case 0:
        case 1:
            phaseR_ = 0;
            phaseG_ = (2*PI/360) * pStep_;
            phaseB_ = (4*PI/360) * pStep_;
            frequencyR_ = float(fStep_) / 100.0;
            frequencyG_ = float(fStep_) / 100.0;
            frequencyB_ = float(fStep_) / 100.0;
            break;
        case 2:
        case 3:
            phaseG_ = 0;
            phaseB_ = (2*PI/360) * pStep_;
            phaseR_ = (4*PI/360) * pStep_;
            frequencyR_ = float(fStep_) / 100.0;
            frequencyG_ = float(fStep_) / 100.0;
            frequencyB_ = float(fStep_) / 100.0;
            break;
        case 4:
        case 5:
            phaseB_ = 0;
            phaseR_ = (2*PI/360) * pStep_;
            phaseG_ = (4*PI/360) * pStep_;
            frequencyR_ = float(fStep_) / 100.0;
            frequencyG_ = float(fStep_) / 100.0;
            frequencyB_ = float(fStep_) / 100.0;
            break;
        }
        default:
            ;//nothing - a still pastel rainbow
    }

    for (light_count_t i=0; i < light_count_; i++)
    {
        int red = sin(frequencyR_*i + phaseR_) * width_ + center_;
        int grn = sin(frequencyG_*i + phaseG_) * width_ + center_;
        int blu = sin(frequencyB_*i + phaseB_) * width_ + center_;
        g35_.set_color(i, G35::MAX_INTENSITY, COLOR(red, grn, blu));
    }

    //set direction: 1 2 .. 98 99 98 .. 2 1
    if (fStep_ == 100)
    {
        fForward_ = false;
    }
    if (fStep_ == -1)
    {
        fForward_ = true;
        turn_++;
    }

    if (fForward_)
    {
        fStep_++;
    }

    if (!fForward_)
    {
        fStep_--;
    }

    pStep_++;
    if (pStep_ == 360)
    {
        pStep_ = 0;
    }

    return delay_;
}
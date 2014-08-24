#ifndef INCLUDE_G35_PROGRAMS_CONTROLLER_FADEIN_FADEOUT_H
#define INCLUDE_G35_PROGRAMS_CONTROLLER_FADEIN_FADEOUT_H

#include <LightProgram.h>
#include <ColorUtils.h>

class ControllerProgramFadeInFadeOut : public LightProgram
{
public:
    ControllerProgramFadeInFadeOut(G35& g35);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    uint32_t Do();

private:

    COLOR_INFO m_colorInfo;
};

#endif  // INCLUDE_G35_PROGRAMS_CONTROLLER_FADEIN_FADEOUT_H


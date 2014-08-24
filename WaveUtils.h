#ifndef INCLUDE_G35_WAVE_UTILS_H
#define INCLUDE_G35_WAVE_UTILS_H

#include <G35.h>

// Colors
//
// All full saturation colors are available.
// 
typedef enum _WAVE_COLORS
{
    WAVE_COLOR_BLACK    = 0,
    WAVE_COLOR_WHITE    = 1,
    WAVE_COLOR_RED      = 2,
    WAVE_COLOR_MAGENTA  = 3,
    WAVE_COLOR_BLUE     = 4,
    WAVE_COLOR_CYAN     = 5,
    WAVE_COLOR_GREEN    = 6,
    WAVE_COLOR_YELLOW   = 7,

    WAVE_COLOR_COUNT // NOT A VALID COLOR
} WAVE_COLORS;


typedef struct _WAVE_INFO
{
    uint8_t Size;
    color_t *Wave;
} WAVE_INFO;


void DestroyColorWave(WAVE_INFO *pInfo);
bool CreateColorWave(WAVE_INFO *pInfo, uint8_t colorCount, uint8_t *colors, uint8_t *holds, uint8_t increments);


uint8_t GetRandomWaveColor(uint8_t NotThisColor1, uint8_t NotThisColor2, uint8_t NotThisColor3);

color_t WaveColorToColor(uint8_t wavecolor);



#endif // INCLUDE_G35_WAVE_UTILS_H

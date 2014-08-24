#ifndef INCLUDE_COLOR_UTILS_H
#define INCLUDE_COLOR_UTILS_H

#include <Arduino.h>
#include <G35.h>
#include <WaveUtils.h>
#include <RainbowUtils.h>

typedef enum {
  COLOR_PALETE_RAINBOW = 0,
  COLOR_PALETE_MAX,
  COLOR_PALETE_ALL,
  COLOR_PALETE_WHEEL,
  COLOR_PALETE_SMOOTH_WHEEL,
  COLOR_PALETE_WAVE,

  COLOR_PALETE_COUNT
} COLOR_PALETE;

typedef struct 
{
    COLOR_PALETE palete;
    uint8_t index;
} COLOR_INFO;


#define RAINBOW_COLOR_COUNT         G35::RB_COUNT /* 7 */
#define MAX_COLOR_COUNT              7
#define ALL_COLOR_COUNT             19
#define WHEEL_COLOR_COUNT           48
#define SMOOTH_WHEEL_COLOR_COUNT    90
//#define WAVE_COLOR_COUNT            WAVE_COLOR_COUNT

#define RAINBOW_PALETE_BASE         (0)
#define MAX_PALETE_BASE             (RAINBOW_PALETE_BASE + RAINBOW_COLOR_COUNT) /* 7 */
#define ALL_PALETE_BASE             (MAX_PALETE_BASE + MAX_COLOR_COUNT) /* 14 */
#define WHEEL_PALETE_BASE           (ALL_PALETE_BASE + ALL_COLOR_COUNT) /* 33 */
#define SMOOTH_WHEEL_PALETE_BASE    (WHEEL_PALETE_BASE + WHEEL_COLOR_COUNT) /* 81 */
#define WAVE_PALETE_BASE            (SMOOTH_WHEEL_PALETE_BASE + SMOOTH_WHEEL_COLOR_COUNT) /* 171 */


#define MAX_PALETE_VALUE            (WAVE_PALETE_BASE + WAVE_COLOR_COUNT)

#define NO_EXCLUDE                  0xFF

color_t GetPaleteColor(const COLOR_INFO *pInfo);
uint8_t GetPaleteMax(COLOR_PALETE palete);
uint8_t GetRandomPaleteColor(COLOR_PALETE palete, uint8_t notThis1, uint8_t notThis2);


void DecodeColorInfo(uint8_t encoded, COLOR_INFO *pInfo);
uint8_t EncodeColorInfo(const COLOR_INFO *pInfo); 


#endif // INCLUDE_COLOR_UTILS_H

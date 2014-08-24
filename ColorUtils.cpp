
#include <ColorUtils.h>
#include <RainbowUtils.h>
#include <WaveUtils.h>


color_t GetPaleteColor(const COLOR_INFO *pInfo)
{
    switch (pInfo->palete)
    {
    case COLOR_PALETE_RAINBOW:
        return G35::rainbow_color((sequence_t)pInfo->index);
    case COLOR_PALETE_MAX:
        return G35::max_color((sequence_t)pInfo->index);
    case COLOR_PALETE_ALL:
        return G35::all_color((sequence_t)pInfo->index);
    case COLOR_PALETE_WHEEL:
        return GetWheelColor(pInfo->index);
    case COLOR_PALETE_SMOOTH_WHEEL:
        return GetSmoothWheelColor(pInfo->index);
    case COLOR_PALETE_WAVE:
        return WaveColorToColor(pInfo->index);
    }

    return COLOR_BLACK;
}


uint8_t GetRandomPaleteColor(COLOR_PALETE palete, uint8_t notThis1, uint8_t notThis2)
{
    uint8_t selected;
    uint8_t bounds;

    bounds = GetPaleteMax(palete);

    do
    {
        // pick a random color
        selected = rand() % bounds;
    } while (selected == notThis1 || selected == notThis2);

    return selected;
}


void DecodeColorInfo(uint8_t value, COLOR_INFO *pInfo)
{
    if (value >= RAINBOW_PALETE_BASE && value < MAX_PALETE_BASE)
    {
        pInfo->palete = COLOR_PALETE_RAINBOW;
        pInfo->index = value;
    }
    else if (value >= MAX_PALETE_BASE && value < ALL_PALETE_BASE)
    {
        pInfo->palete = COLOR_PALETE_MAX;
        pInfo->index = value - MAX_PALETE_BASE;
    }
    else if (value >= ALL_PALETE_BASE && value < WHEEL_PALETE_BASE)
    {
        pInfo->palete = COLOR_PALETE_ALL;
        pInfo->index = value - ALL_PALETE_BASE;
    }
    else if (value >= WHEEL_PALETE_BASE && value < SMOOTH_WHEEL_PALETE_BASE)
    {
        pInfo->palete = COLOR_PALETE_WHEEL;
        pInfo->index = value - WHEEL_PALETE_BASE;
    }
    else if (value >= SMOOTH_WHEEL_PALETE_BASE && value < WAVE_PALETE_BASE)
    {
        pInfo->palete = COLOR_PALETE_SMOOTH_WHEEL;
        pInfo->index = value - SMOOTH_WHEEL_PALETE_BASE;
    }
    else if (value >= WAVE_PALETE_BASE && value < (WAVE_PALETE_BASE + WAVE_COLOR_COUNT))
    {
        pInfo->palete = COLOR_PALETE_WAVE;
        pInfo->index = value - WAVE_PALETE_BASE;
    }
    else
    {
        pInfo->palete = COLOR_PALETE_RAINBOW;
        pInfo->index = 0;
    }
}

uint8_t GetPaleteMax(COLOR_PALETE palete)
{
    switch (palete)
    {
    case COLOR_PALETE_RAINBOW:      return RAINBOW_COLOR_COUNT;
    case COLOR_PALETE_MAX:          return MAX_COLOR_COUNT;
    case COLOR_PALETE_ALL:          return ALL_COLOR_COUNT;
    case COLOR_PALETE_WHEEL:        return WHEEL_COLOR_COUNT;
    case COLOR_PALETE_SMOOTH_WHEEL: return SMOOTH_WHEEL_COLOR_COUNT;
    case COLOR_PALETE_WAVE:         return WAVE_COLOR_COUNT;
    default:                        return 0;
    }
}


uint8_t EncodeColorInfo(const COLOR_INFO *pInfo)
{
    uint8_t value = 0;

    switch (pInfo->palete)
    {
    case COLOR_PALETE_RAINBOW:
        value = RAINBOW_PALETE_BASE;
        break;
    case COLOR_PALETE_MAX:
        value = MAX_PALETE_BASE;
        break;
    case COLOR_PALETE_ALL:
        value = ALL_PALETE_BASE;
        break;
    case COLOR_PALETE_WHEEL:
        value =  WHEEL_PALETE_BASE;
        break;
    case COLOR_PALETE_SMOOTH_WHEEL:
        value = SMOOTH_WHEEL_PALETE_BASE;
        break;
    case COLOR_PALETE_WAVE:
        value = WAVE_PALETE_BASE;
        break;
    }

    return value + pInfo->index;
}


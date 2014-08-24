
#include <DebugConfig.h>
#if DEBUG_WAVE_UTILS
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif


#include <WaveUtils.h>

gradient_t NormalizeColorChannel(gradient_t value)
{
    if (value > CHANNEL_MAX)
    {
        return CHANNEL_MAX;
    }
    else if (value < 0)
    {
        return 0;
    }
    return value;
}

void DestroyColorWave(WAVE_INFO *pInfo)
{
    if (pInfo->Wave)
    {
        free(pInfo->Wave);
    }
    memset(pInfo, 0, sizeof(WAVE_INFO));
}

// increments is the number of increments between two colors.
//
// colorCount > 0
// 1 <= increments <= 15 
bool CreateColorWave(WAVE_INFO *pInfo, uint8_t colorCount, uint8_t *colors, uint8_t *holds, uint8_t increments)
{
    // Validate input.
#if DEBUG_ENABLED
    if (colorCount < 2)
    {
        DebugPrintf("Invalid parameters in CreateColorWave\n");
        return false;
    }
#endif
    if (increments == 0 || increments > 15)
    {
        increments = 15;
    }

    // Allocate a buffer for the color wave.
    // All ramps are the same so start with number of ramps x number of colors in a ramp
    // then add all color holds.
    DestroyColorWave(pInfo);
    pInfo->Size = (byte)((colorCount - 1) * (increments - 1));
    for (uint8_t i = 0; i < colorCount; i++)
    {
        pInfo->Size += holds[i];
    }
    pInfo->Wave = static_cast<color_t *>(malloc(sizeof(color_t) * pInfo->Size));
    if (pInfo->Wave == NULL)
    {
        DebugPrintf("Failed to allocate color wave\n");
        return false;
    }

    // Calculate the size of each increment in the ramp between colors (ie the slope of the ramp).
    // For example, rampIncrements of 3 means there are 3 steps between min and max values.
    //   0 - 5 - 10 - 15
    gradient_t increment = 1;
    if (increments < 15)
    {
        increment = (15 / (gradient_t)increments);
    }

    // Build the wave
    uint8_t waveIndex = 0;
    for (uint8_t i = 0; i < colorCount; i++)
    {
        // Get color channel values of current color and setup ramp to next color.
        gradient_t red = 0;
        gradient_t green = 0;
        gradient_t blue = 0;

        gradient_t redIncrement = 0;
        gradient_t greenIncrement = 0;
        gradient_t blueIncrement = 0;

        switch (colors[i])
        {
            case WAVE_COLOR_RED:
                red = 15;
                redIncrement = -1 * increment;
                break;
            case WAVE_COLOR_GREEN:
                green = 15;
                greenIncrement = -1 * increment;
                break;
            case WAVE_COLOR_BLUE:
                blue = 15;
                blueIncrement = -1 * increment;
                break;
            case WAVE_COLOR_YELLOW:
                red = 15;
                green = 15;
                redIncrement = -1 * increment;
                greenIncrement = -1 * increment;
                break;
            case WAVE_COLOR_MAGENTA:
                red = 15;
                blue = 15;
                redIncrement = -1 * increment;
                blueIncrement = -1 * increment;
                break;
            case WAVE_COLOR_CYAN:
                green = 15;
                blue = 15;
                greenIncrement = -1 * increment;
                blueIncrement = -1 * increment;
                break;
            case WAVE_COLOR_WHITE:
                red = 15;
                green = 15;
                blue = 15;
                redIncrement = -1 * increment;
                greenIncrement = -1 * increment;
                blueIncrement = -1 * increment;
                break;
            default:
            case WAVE_COLOR_BLACK:
                red = 0;
                green = 0;
                blue = 0;
                break;
        }

        // Add hold entries of current color.
        for (uint8_t j = 0; j < holds[i]; j++)
        {
            pInfo->Wave[waveIndex++] = COLOR((uint8_t)red, (uint8_t)green, (uint8_t)blue);
        }

        // Add ramp to next color if there is one.
        if (i < (colorCount - 1))
        {
            switch (colors[i + 1])
            {
                case WAVE_COLOR_RED:
                    redIncrement += increment;
                    break;
                case WAVE_COLOR_GREEN:
                    greenIncrement += increment;
                    break;
                case WAVE_COLOR_BLUE:
                    blueIncrement += increment;
                    break;
                case WAVE_COLOR_YELLOW:
                    redIncrement += increment;
                    greenIncrement += increment;
                    break;
                case WAVE_COLOR_MAGENTA:
                    redIncrement += increment;
                    blueIncrement += increment;
                    break;
                case WAVE_COLOR_CYAN:
                    greenIncrement += increment;
                    blueIncrement += increment;
                    break;
                case WAVE_COLOR_WHITE:
                    redIncrement += increment;
                    greenIncrement += increment;
                    blueIncrement += increment;
                    break;
                default:
                case WAVE_COLOR_BLACK:
                    break;
            }

            for (uint8_t j = 0; j < increments - 1; j++)
            {
                red = NormalizeColorChannel(red + redIncrement);
                green = NormalizeColorChannel(green + greenIncrement);
                blue = NormalizeColorChannel(blue + blueIncrement);

                pInfo->Wave[waveIndex++] = COLOR((uint8_t)red, (uint8_t)green, (uint8_t)blue);
            }
        }
    }

    return true;
}

uint8_t GetRandomWaveColor(uint8_t NotThisColor1, uint8_t NotThisColor2, uint8_t NotThisColor3)
{
    uint8_t targetColor;

    do
    {
        // pick a random color
        targetColor = rand() % WAVE_COLOR_COUNT;

    } while (targetColor == NotThisColor1 || targetColor == NotThisColor2 || targetColor == NotThisColor3);
    return targetColor;
}

color_t WaveColorToColor(uint8_t wavecolor)
{
    switch (wavecolor % WAVE_COLOR_COUNT)
    {
    case WAVE_COLOR_BLACK: return COLOR_BLACK;
    case WAVE_COLOR_BLUE: return COLOR_BLUE;
    case WAVE_COLOR_CYAN: return COLOR_CYAN;
    case WAVE_COLOR_GREEN: return COLOR_GREEN;
    case WAVE_COLOR_MAGENTA: return COLOR_MAGENTA;
    case WAVE_COLOR_RED: return COLOR_RED;
    case WAVE_COLOR_WHITE: return COLOR_WHITE;
    case WAVE_COLOR_YELLOW: return COLOR_YELLOW;   
    }

    return COLOR_BLACK;
}




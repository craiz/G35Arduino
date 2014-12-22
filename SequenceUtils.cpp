
#include <DebugConfig.h>
#if DEBUG_SEQUENCE_UTILS
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <G35.h>
#include <SequenceUtils.h>

SEQUENCE_INFO *gpActiveSequence = NULL;
void SetActiveSequence(SEQUENCE_INFO *pInfo)
{
#if DEBUG_ENABLED
    if (pInfo)
    {
        DebugPrintf("Sequence Info:\n");
        DebugPrintf("  BulbsPerPosition: %u\n", pInfo->BulbsPerPosition);
        DebugPrintf("  Size: %u\n", pInfo->Size);

        uint8_t r, g, b;
        for (uint8_t i = 0; i < pInfo->Size; i++)
        {
            r = pInfo->Colors[i] & 0x0F;
            g = (pInfo->Colors[i] >> 4) & 0x0F;
            b = (pInfo->Colors[i] >> 8) & 0x0F;
            
            DebugPrintf("  Color %u: %u,%u,%u\n", i, r, g, b);
        }
    }
#endif

    gpActiveSequence = pInfo;
}

color_t Sequencer(sequence_t sequence)
{
    if (!gpActiveSequence)
    {
        DebugPrintf("No active sequence\n");
        return COLOR_BLACK;
    }
    else
    {
        return gpActiveSequence->Colors[sequence % gpActiveSequence->Size];
    }
}

uint8_t SetupControllerSequence(ProgramCommand* pProgram, pattern_t pattern)
{
    // Extra Data Parameters:
    // ----------------------
    // Bulbs Per Position (8-bit)   = ProgramData + 0
    // Color Count (8-bit)          = ProgramData + 1
    // Color 1 (16-bit)             = ProgramData + 2
    // Color N (16-bit)             = ProgramData + 2 + ((N - 1) * 2)

    uint8_t * extraData = (uint8_t *)pProgram + sizeof(ProgramCommand);
    color_t * colors = (color_t *)&extraData[2];

    switch (pattern)
    {
    default:
    case SEQUENCE_PATTERN_RED_GREEN:
        pProgram->pattern = SEQUENCE_PATTERN_RED_GREEN;

        extraData[0] = 5;
        extraData[1] = 2;

        colors[0] = COLOR_GREEN;
        colors[1] = COLOR_RED;
        break;

    case SEQUENCE_PATTERN_HALLOWEEN:
        pProgram->pattern = SEQUENCE_PATTERN_HALLOWEEN;

        extraData[0] = 3;
        extraData[1] = 4;

        colors[0] = COLOR_ORANGE;
        colors[1] = COLOR_BLACK;
        colors[2] = COLOR_GREEN;
        colors[3] = COLOR_PURPLE;
        break;

    case SEQUENCE_PATTERN_CHRISTMAS:
        pProgram->pattern = SEQUENCE_PATTERN_CHRISTMAS;

        extraData[0] = 1;
        extraData[1] = 9;

        colors[0] = COLOR_WARMWHITE;
        colors[1] = COLOR_WARMWHITE;
        colors[2] = COLOR_WARMWHITE;
        colors[3] = COLOR_GREEN;
        colors[4] = COLOR_RED;
        colors[5] = COLOR_GREEN;
        colors[6] = COLOR_WARMWHITE;
        colors[7] = COLOR_WARMWHITE;
        colors[8] = COLOR_WARMWHITE;

        break;    

    case SEQUENCE_PATTERN_ICE:
        pProgram->pattern = SEQUENCE_PATTERN_ICE;

        extraData[0] = 3;
        extraData[1] = 2;

        colors[0] = COLOR_WHITE;
        colors[1] = COLOR_BLUE;
        break;

    case SEQUENCE_PATTERN_CANDY_CANE:
        pProgram->pattern = SEQUENCE_PATTERN_CANDY_CANE;

        extraData[0] = 3;
        extraData[1] = 2;

        colors[0] = COLOR_WHITE;
        colors[1] = COLOR_RED;
        break;

    case SEQUENCE_PATTERN_UW:
        pProgram->pattern = SEQUENCE_PATTERN_UW;
    
        extraData[0] = 3;
        extraData[1] = 2;
    
        colors[0] = COLOR_INDIGO;
        colors[1] = COLOR_YELLOW;
        break;

    // TODO: Fix this!
    case SEQUENCE_PATTERN_SEAHAWKS_LONG:
        pProgram->pattern = SEQUENCE_PATTERN_SEAHAWKS_LONG;
    
        extraData[0] = 5;
        extraData[1] = 2;
    
        colors[0] = COLOR_BLUE;
        colors[1] = COLOR_GREEN;
        break;

    case SEQUENCE_PATTERN_SEAHAWKS_SHORT:
        pProgram->pattern = SEQUENCE_PATTERN_SEAHAWKS_SHORT;
    
        extraData[0] = 2;
        extraData[1] = 2;
    
        colors[0] = COLOR_BLUE;
        colors[1] = COLOR_GREEN;
        break;
    };

    return 2 + (extraData[1] * sizeof(color_t));
}


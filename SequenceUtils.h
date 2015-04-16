/*
*/

#ifndef INCLUDE_G35_SEQUENCE_UTILS_H
#define INCLUDE_G35_SEQUENCE_UTILS_H

#include <ColorNodeCommands.h>

typedef struct _SEQUENCE_INFO
{
    uint8_t Size;
    uint8_t BulbsPerPosition;
    color_t *Colors;
} SEQUENCE_INFO;

void SetActiveSequence(SEQUENCE_INFO *pInfo);
color_t Sequencer(sequence_t sequence);

uint8_t SetupControllerSequence(ProgramCommand* pProgram, pattern_t pattern);

typedef enum
{
    SEQUENCE_PATTERN_SOLID_COLORS=0,            // 0
    SEQUENCE_PATTERN_MULTI_COLORS,              // 1
    SEQUENCE_PATTERN_TWO_COLORS,                // 2
    SEQUENCE_PATTERN_RED_GREEN,                 // 3
    SEQUENCE_PATTERN_RED_WHITE_GREEN,           // 4
    SEQUENCE_PATTERN_RED_WHITE_BLUE,            // 5
    SEQUENCE_PATTERN_RAINBOW,                   // 6
    SEQUENCE_PATTERN_PULSE,                     // 7
    SEQUENCE_PATTERN_PURPLY_BLUE,               // 8
    SEQUENCE_PATTERN_VALENTINES,                // 9
    SEQUENCE_PATTERN_BLUE_TRIAD,                // 10
    SEQUENCE_PATTERN_BLUE_TETRAD,               // 11
    SEQUENCE_PATTERN_PURPLE_TETRAD,             // 12
    SEQUENCE_PATTERN_GREEN_TETRAD,              // 13
    SEQUENCE_PATTERN_RED_CYAN,                  // 14
    SEQUENCE_PATTERN_GREEN_MAGENTA,             // 15
    SEQUENCE_PATTERN_BLUE_YELLOW,               // 16
    SEQUENCE_PATTERN_GREEN_BLUE,                // 17
    SEQUENCE_PATTERN_BLUE_RED,                  // 18
    SEQUENCE_PATTERN_CYAN_MAGENTA,              // 19
    SEQUENCE_PATTERN_MAGENTA_YELLOW,            // 20
    SEQUENCE_PATTERN_YELLOW_CYAN,               // 21
    SEQUENCE_PATTERN_RED_GREEN_BLUE,            // 22
    SEQUENCE_PATTERN_CYAN_YELLOW_MAGENTA,       // 23
    SEQUENCE_PATTERN_RED_GREEN_BLUE_YELLOW,     // 24
    SEQUENCE_PATTERN_PASTEL_RED_GREEN_BLUE,     // 25
    SEQUENCE_PATTERN_RED_ACCENTED_ANALOGIC,     // 26
    SEQUENCE_PATTERN_GREEN_ACCENTED_ANALOGIC,   // 27
    SEQUENCE_PATTERN_BLUE_ACCENTED_ANALOGIC,    // 28
    SEQUENCE_PATTERN_RED_CYAN_GREEN_MAGENTA_BLUE_YELLOW,    //29
    SEQUENCE_PATTERN_HALLOWEEN,                 // 30
    SEQUENCE_PATTERN_CHRISTMAS,                 // 31
    SEQUENCE_PATTERN_ICE,                       // 32
    SEQUENCE_PATTERN_CANDY_CANE,                // 33
    SEQUENCE_PATTERN_UW,                        // 34
    SEQUENCE_PATTERN_SEAHAWKS,                  // 35


    SEQUENCE_PATTERN_COUNT  
} SEQUENCE_PATTERN;

#if 0
color_t SequencePastelRedGreenBlue(sequence_t sequence);
color_t SequenceRedGreenBlueYellow(sequence_t sequence);
color_t SequenceRedWhiteBlue(sequence_t sequence);
color_t SequenceRedWhiteGreen(sequence_t sequence);
color_t SequenceRedCyan(sequence_t sequence);
color_t SequenceGreenMagenta(sequence_t sequence);
color_t SequenceBlueYellow(sequence_t sequence);
color_t SequenceRedGreen(sequence_t sequence);
color_t SequenceGreenBlue(sequence_t sequence);
color_t SequenceBlueRed(sequence_t sequence);
color_t SequenceCyanMagenta(sequence_t sequence);
color_t SequenceMagentaYellow(sequence_t sequence);
color_t SequenceYellowCyan(sequence_t sequence);
color_t SequenceRedGreenBlue(sequence_t sequence);
color_t SequenceCyanYellowMagenta(sequence_t sequence);
color_t SequenceRedCyanGreenMagentaBlueYellow(sequence_t sequence);
color_t SequencePurplyBlue(sequence_t sequence);
color_t SequenceValentines(sequence_t sequence);
color_t SequenceBlueTriad(sequence_t sequence);
color_t SequenceBlueBronze(sequence_t sequence);
color_t SequenceBlueTetrad(sequence_t sequence);
color_t SequencePurpleTetrad(sequence_t sequence);
color_t SequenceGreenTetrad(sequence_t sequence);
color_t SequenceGreenAccentedAnalogic(sequence_t sequence);
color_t SequenceRedAccentedAnalogic(sequence_t sequence);
color_t SequenceBlueAccentedAnalogic(sequence_t sequence);
color_t SequenceHalloween(sequence_t sequence);


bool SequencePulser(sequence_t sequence, color_t& color, uint8_t& intensity);
#endif

#endif //INCLUDE_G35_SEQUENCE_UTILS_H

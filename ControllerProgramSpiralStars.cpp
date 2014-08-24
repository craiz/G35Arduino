#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_CONTROLLER_SPIRAL_STARS
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <ControllerProgramSpiralStars.h>
#include <ColorNodeCommands.h>
#include <ColorNodeSendCommand.h>
#include <LightProgram.h>
#include <WaveUtils.h>
#include <G35String.h>


#if 0
    // Every Other
    uint8_t every_other[2] = { STRING_GROUP_B_TREE_1 | STRING_GROUP_B_TREE_3 | STRING_GROUP_B_TREE_5 | STRING_GROUP_B_TREE_7 | STRING_GROUP_B_TREE_9 | STRING_GROUP_B_TREE_11 | STRING_GROUP_B_TREE_13,
                               STRING_GROUP_B_TREE_2 | STRING_GROUP_B_TREE_4 | STRING_GROUP_B_TREE_6 | STRING_GROUP_B_TREE_8 | STRING_GROUP_B_TREE_10 | STRING_GROUP_B_TREE_12 | STRING_GROUP_B_TREE_14 };
    uint8_t every_other_count = 2;

    // Every third
    uint8_t every_third[3] = { STRING_GROUP_B_TREE_1 | STRING_GROUP_B_TREE_4 | STRING_GROUP_B_TREE_7 | STRING_GROUP_B_TREE_10 | STRING_GROUP_B_TREE_13,
                               STRING_GROUP_B_TREE_2 | STRING_GROUP_B_TREE_5 | STRING_GROUP_B_TREE_8 | STRING_GROUP_B_TREE_11 | STRING_GROUP_B_TREE_14,
                               STRING_GROUP_B_TREE_3 | STRING_GROUP_B_TREE_6 | STRING_GROUP_B_TREE_9 | STRING_GROUP_B_TREE_12 };
    uint8_t every_third_count = 3;

    // Every fourth
    uint8_t every_fourth[4] = { STRING_GROUP_B_TREE_1 | STRING_GROUP_B_TREE_5 | STRING_GROUP_B_TREE_9 | STRING_GROUP_B_TREE_13,
                                STRING_GROUP_B_TREE_2 | STRING_GROUP_B_TREE_6 | STRING_GROUP_B_TREE_10 | STRING_GROUP_B_TREE_14,
                                STRING_GROUP_B_TREE_3 | STRING_GROUP_B_TREE_7 | STRING_GROUP_B_TREE_11,
                                STRING_GROUP_B_TREE_4 | STRING_GROUP_B_TREE_8 | STRING_GROUP_B_TREE_12 };
    uint8_t every_fourth_count = 4;

    // every fifth
    uint8_t every_fifth[5] = { STRING_GROUP_B_TREE_1 | STRING_GROUP_B_TREE_6 | STRING_GROUP_B_TREE_11,
                               STRING_GROUP_B_TREE_2 | STRING_GROUP_B_TREE_7 | STRING_GROUP_B_TREE_12,
                               STRING_GROUP_B_TREE_3 | STRING_GROUP_B_TREE_8 | STRING_GROUP_B_TREE_13,
                               STRING_GROUP_B_TREE_4 | STRING_GROUP_B_TREE_9 | STRING_GROUP_B_TREE_14,
                               STRING_GROUP_B_TREE_5 | STRING_GROUP_B_TREE_10 };
    uint8_t every_fifth_count = 5;

    // Every sixth
    uint8_t every_sixth[6] = { STRING_GROUP_B_TREE_1 | STRING_GROUP_B_TREE_7 | STRING_GROUP_B_TREE_13,
                               STRING_GROUP_B_TREE_2 | STRING_GROUP_B_TREE_8 | STRING_GROUP_B_TREE_14,
                               STRING_GROUP_B_TREE_3 | STRING_GROUP_B_TREE_9,
                               STRING_GROUP_B_TREE_4 | STRING_GROUP_B_TREE_10,
                               STRING_GROUP_B_TREE_5 | STRING_GROUP_B_TREE_11,
                               STRING_GROUP_B_TREE_6 | STRING_GROUP_B_TREE_12 };
    uint8_t every_sixth_count = 6;

    // Every seventh
    uint8_t every_seventh[7] = { STRING_GROUP_B_TREE_1 | STRING_GROUP_B_TREE_8,
                                 STRING_GROUP_B_TREE_2 | STRING_GROUP_B_TREE_9,
                                 STRING_GROUP_B_TREE_3 | STRING_GROUP_B_TREE_10,
                                 STRING_GROUP_B_TREE_4 | STRING_GROUP_B_TREE_11,
                                 STRING_GROUP_B_TREE_5 | STRING_GROUP_B_TREE_12,
                                 STRING_GROUP_B_TREE_6 | STRING_GROUP_B_TREE_13,
                                 STRING_GROUP_B_TREE_7 | STRING_GROUP_B_TREE_14 };
    uint8_t every_seventh_count = 7;    

    // Every eighth
    uint8_t every_eighth[8] = { STRING_GROUP_B_TREE_1 | STRING_GROUP_B_TREE_9,
                                STRING_GROUP_B_TREE_2 | STRING_GROUP_B_TREE_10,
                                STRING_GROUP_B_TREE_3 | STRING_GROUP_B_TREE_11,
                                STRING_GROUP_B_TREE_4 | STRING_GROUP_B_TREE_12,
                                STRING_GROUP_B_TREE_5 | STRING_GROUP_B_TREE_13,
                                STRING_GROUP_B_TREE_6 | STRING_GROUP_B_TREE_14,
                                STRING_GROUP_B_TREE_7,
                                STRING_GROUP_B_TREE_8 }
    uint8_t every_eighth_count = 8;
#endif



/*

*/

ControllerProgramSpiralStars::ControllerProgramSpiralStars(G35& g35)
  : LightProgram(g35)
  , m_WhiteTip(false)
{
    DebugPrintf("ControllerProgramSpiralStars\n");
}

#define TICK_GAP_MIN (0)
#define TICK_GAP_MAX (1)
#define POSITION_GAP_MIN (2)
#define POSITION_GAP_MAX (3)
#define STARS_MAX (4)

bool ControllerProgramSpiralStars::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    if (option)
    {
        m_WhiteTip = true;
    }

    switch (pattern)
    {
    case SpiralStarPattern_Random:
        break;
    default:
    case SpiralStarPattern_Blue:
        m_WaveColor = WAVE_COLOR_BLUE;
        break;
    case SpiralStarPattern_Red:
        m_WaveColor = WAVE_COLOR_RED;
        break;
    case SpiralStarPattern_Green:
        m_WaveColor = WAVE_COLOR_GREEN;
        break;        
    }

    memset(payloadData, 0, MAX_COMMAND_BUFFER);
    payloadSize = sizeof(ProgramCommand) + 5;
    ProgramCommand *pProgram = (ProgramCommand *)payloadData;
    byte* extra_data = (byte *)(payloadData + sizeof(ProgramCommand));
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.layout = STRING_LAYOUT_LINEAR;
    pProgram->command.option = COMMAND_OPTION_GROUP_B;
    pProgram->command.address = 0xFFFF & ~0xC000; // All tree but trunk and top

    pProgram->program = COLOR_NODE_PROGRAM_SHOOTING_STARS;

    pProgram->option = 2 << 4;
    pProgram->option |= PROGRAM_OPTION_FIXED | PROGRAM_OPTION_WAIT;
    if (m_WhiteTip)
    {
        pProgram->option |= OPTION_BIT_2;
    }
    pProgram->delay = 0;

    pProgram->pattern = m_WaveColor << 4;
    pProgram->pattern |= 10;


    extra_data[TICK_GAP_MIN] = 0;
    extra_data[TICK_GAP_MAX] = 0;
    extra_data[POSITION_GAP_MIN] = 0;
    extra_data[POSITION_GAP_MAX] = 0;
    extra_data[STARS_MAX] = 10;

    SendCommand();

    delay_ = 50;

    m_StarGap = 5;
    m_CyclesUntilStar = 0;
    m_Address = 0;
    m_LeftToRight = true;

    if (m_LeftToRight)
    {
        m_NewStarAddress = 0x0001;
    }
    else
    {
        m_NewStarAddress = 0x8000;
    }

    return true;
}

uint32_t ControllerProgramSpiralStars::Do()
{
    if (m_LeftToRight)
    {
        m_Address = m_Address << 1;
    }
    else
    {
        m_Address = m_Address >> 1;
    }
    if (m_CyclesUntilStar == 0)
    {
        m_Address |= m_NewStarAddress;
        m_CyclesUntilStar = m_StarGap;
    }
    else
    {
        m_CyclesUntilStar--;
    }

    // Send a kick
    payloadSize = sizeof(Command);
    Command *pCommand = (Command *)payloadData;
    pCommand->type = COMMAND_KICK;
    pCommand->option = COMMAND_OPTION_GROUP_B;
    pCommand->address = m_Address & ~0xC000;

    SendCommand();

    return delay_;
}


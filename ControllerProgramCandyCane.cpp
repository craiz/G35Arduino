#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_CONTROLLER_CANDY_CANE
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <ControllerProgramCandyCane.h>
#include <ColorNodeCommands.h>
#include <ColorNodeSendCommand.h>
#include <LightProgram.h>
#include <ColorUtils.h>
#include <G35String.h>
#include <SequenceUtils.h>



/*
    Place a Candy Cane (red\white) pattern on the house.
*/

ControllerProgramCandyCane::ControllerProgramCandyCane(G35& g35)
  : LightProgram(g35)
{
    DebugPrintf("ControllerProgramCandyCane\n");
}

bool ControllerProgramCandyCane::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    ProgramCommand* pProgram;
    uint8_t * extraData;
    uint8_t * colors;
    uint8_t * holds;

    // setup colors
    COLOR_INFO colorInfo;
    byte encodedRed;
    byte encodedWhite;

    colorInfo.palete = COLOR_PALETE_ALL;
    colorInfo.index = 2;
    encodedRed = EncodeColorInfo(&colorInfo);

    colorInfo.palete = COLOR_PALETE_ALL;
    colorInfo.index = 0;
    encodedWhite = EncodeColorInfo(&colorInfo);

    // Setup parameters common to raw commands
    memset(payloadData, 0, MAX_COMMAND_BUFFER);
    RawCommand *rawCommand = (RawCommand *)payloadData;
    byte* bulb_data = (byte *)(payloadData + sizeof(RawCommand));
    rawCommand->command.type = COMMAND_RAW;
    rawCommand->command.layout = STRING_LAYOUT_LINEAR;
    rawCommand->bulb_delay = 30;
    rawCommand->intensity = G35::MAX_INTENSITY;

    // Small Garage Door
    // Red with white corners
    DebugPrintf("Configuring garage door small\n");
    payloadSize = sizeof(RawCommand) + 36;
    rawCommand->command.address = STRING_ID_DOOR_SMALL;
    rawCommand->command.option = COMMAND_OPTION_DEFER;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 35;
    memset(bulb_data, encodedRed, 36);
    bulb_data[11] = encodedWhite;
    bulb_data[24] = encodedWhite;
    SendCommand();

    // Large Garage Door
    // Red with white corners
    DebugPrintf("Configuring garage door big\n");
    payloadSize = sizeof(RawCommand) + 50;
    rawCommand->command.address = STRING_ID_DOOR_BIG;
    rawCommand->command.option = COMMAND_OPTION_DEFER;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 49;
    memset(bulb_data, encodedRed, 50);
    bulb_data[11] = encodedWhite;
    bulb_data[38] = encodedWhite;
    SendCommand();

    // Bonus Room Window
    // Red with white corners
    DebugPrintf("Configuring bonus room window\n");
    payloadSize = sizeof(RawCommand) + 36;
    rawCommand->command.address = STRING_ID_WINDOW_BONUS;
    rawCommand->command.option = COMMAND_OPTION_DEFER;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 35;
    memset(bulb_data, encodedRed, 36);
    bulb_data[0] = encodedWhite;
    bulb_data[7] = encodedWhite;
    bulb_data[18] = encodedWhite;
    bulb_data[25] = encodedWhite;
    SendCommand();

    // Living Room Windows
    // Red with white corners
    DebugPrintf("Configuring living room window\n");
    payloadSize = sizeof(RawCommand) + 50;
    rawCommand->command.address = STRING_ID_WINDOW_LIVING;
    rawCommand->command.option = COMMAND_OPTION_DEFER;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 49;
    memset(bulb_data, encodedRed, 50);
    bulb_data[0] = encodedWhite;
    bulb_data[13] = encodedWhite;
    bulb_data[25] = encodedWhite;
    bulb_data[38] = encodedWhite;
    SendCommand();

    // Front Door
    // Red with white corners
    DebugPrintf("Configuring front door window\n");
    payloadSize = sizeof(RawCommand) + 50;
    rawCommand->command.address = STRING_ID_DOOR_FRONT;
    rawCommand->command.option = COMMAND_OPTION_DEFER;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 49;
    memset(bulb_data, encodedRed, 50);
    bulb_data[20] = encodedWhite;
    bulb_data[29] = encodedWhite;
    SendCommand();

    // Star
    // Red with white tips
    DebugPrintf("Configuring star\n");
    payloadSize = sizeof(RawCommand) + 50;
    rawCommand->command.address = STRING_ID_STAR;
    rawCommand->command.option = COMMAND_OPTION_DEFER;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 49;
    memset(bulb_data, encodedRed, 50);
    bulb_data[0] = encodedWhite;
    bulb_data[5] = encodedWhite;
    bulb_data[10] = encodedWhite;
    bulb_data[15] = encodedWhite;
    bulb_data[20] = encodedWhite;
    bulb_data[25] = encodedWhite;
    bulb_data[30] = encodedWhite;
    bulb_data[35] = encodedWhite;
    bulb_data[40] = encodedWhite;
    bulb_data[45] = encodedWhite;
    SendCommand();

    // Snowflake big is a red/white wave
    pProgram = (ProgramCommand *)payloadData;
    memset(pProgram, 0, sizeof(ProgramCommand));
    pProgram->command.type= COMMAND_PROGRAM;
    pProgram->command.address = STRING_ID_SNOWFLAKE;
    pProgram->command.option = COMMAND_OPTION_DEFER;
    pProgram->command.layout = STRING_LAYOUT_RINGS_CENTER;
    pProgram->delay = 50;
    pProgram->pattern = 3; // number of colors
    pProgram->option = 15 << 4; // ramp size
    pProgram->option |= PROGRAM_OPTION_FIXED;
    pProgram->program = COLOR_NODE_PROGRAM_WAVE;
    
    extraData = payloadData + sizeof(ProgramCommand);
    extraData[0] = 0; // pixel count
    extraData[1] = 0; // pixel distribution
    extraData[2] = 1; // span size
    colors = &extraData[3];
    holds = colors + pProgram->pattern;
    colors[0] = WAVE_COLOR_WHITE;
    colors[1] = WAVE_COLOR_RED;
    colors[2] = WAVE_COLOR_WHITE;
    holds[0] = 1;
    holds[1] = 15;
    holds[2] = 0;

    payloadSize = sizeof(ProgramCommand) + (pProgram->pattern * 2) + 3;

    SendCommand();

    // TODO: Fix snowflake grouping.
    pProgram->command.address = STRING_ID_SNOWFLAKE_2;
    SendCommand();

    // Roof line is a red/white wave
    DebugPrintf("Configuring roof\n");
    pProgram = (ProgramCommand *)payloadData;
    memset(pProgram, 0, sizeof(ProgramCommand));
    pProgram->command.type= COMMAND_PROGRAM;
    pProgram->command.address = STRING_GROUP_A_ROOF;
    pProgram->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_A;
    pProgram->command.layout = STRING_LAYOUT_LINEAR;
    pProgram->delay = 50;
    pProgram->pattern = 3; // number of colors
    pProgram->option = 15 << 4; // ramp size
    pProgram->option |= PROGRAM_OPTION_FIXED;
    pProgram->program = COLOR_NODE_PROGRAM_WAVE;
    
    extraData = payloadData + sizeof(ProgramCommand);
    extraData[0] = 3; // pixel count
    extraData[1] = 6; // pixel distribution
    extraData[2] = 1; // span size
    colors = &extraData[3];
    holds = colors + pProgram->pattern;
    colors[0] = WAVE_COLOR_WHITE;
    colors[1] = WAVE_COLOR_RED;
    colors[2] = WAVE_COLOR_WHITE;
    holds[0] = 1;
    holds[1] = 15;
    holds[2] = 0;

    payloadSize = sizeof(ProgramCommand) + (pProgram->pattern * 2) + 3;

    SendCommand();

    // Yard, Bushes
    // Slow Red/White chase
    DebugPrintf("Configuring yard\n");
    pProgram = (ProgramCommand *)payloadData;
    payloadSize = sizeof(ProgramCommand);
    memset(pProgram, 0, sizeof(ProgramCommand));
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.address = STRING_GROUP_A_YARD | STRING_GROUP_A_BUSHES;
    pProgram->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_A;
    pProgram->command.layout = STRING_LAYOUT_LINEAR;
    pProgram->option = PROGRAM_OPTION_IMMEDIATE | PROGRAM_OPTION_FORWARD;
    pProgram->program = COLOR_NODE_PROGRAM_CHASE;
    pProgram->delay = 500;

    // Set up the extra data needed for the chase program.
    uint8_t extraDataSize = SetupControllerSequence(pProgram, SEQUENCE_PATTERN_CANDY_CANE);
    payloadSize += extraDataSize;

    SendCommand();

    // Tree top:
    // red/white wave vertical lines
    pProgram = (ProgramCommand *)payloadData;
    pProgram->command.type= COMMAND_PROGRAM;
    pProgram->command.address = STRING_ID_TREE_TOP;
    pProgram->command.option = COMMAND_OPTION_DEFER;
    pProgram->command.layout = STRING_LAYOUT_VERTICAL_LINES;
    pProgram->delay = 50;
    pProgram->pattern = 3; // number of colors
    pProgram->option = 15 << 4; // ramp size
    pProgram->option |= PROGRAM_OPTION_FIXED;
    pProgram->program = COLOR_NODE_PROGRAM_WAVE;
    
    extraData = payloadData + sizeof(ProgramCommand);
    extraData[0] = 7; // pixel count
    extraData[1] = 0; // pixel distribution
    extraData[2] = 1; // span size
    colors = &extraData[3];
    holds = colors + pProgram->pattern;
    colors[0] = WAVE_COLOR_RED;
    colors[1] = WAVE_COLOR_WHITE;
    colors[2] = WAVE_COLOR_RED;
    holds[0] = 5;
    holds[1] = 0;
    holds[2] = 0;

    payloadSize = sizeof(ProgramCommand) + (pProgram->pattern * 2) + 3;

    SendCommand();

    // Tree
    // Red with white tip spiral shooting stars
    DebugPrintf("Configuring tree\n");
    m_SpiralTree.SetWhiteTip(true);
    m_SpiralTree.SetDelay(30);
    m_SpiralTree.SetDefer(true);
    m_SpiralTree.SetStarGap(3);
    m_SpiralTree.SetStarSize(10);
    m_SpiralTree.SetColors(SpiralTreeStarsColors_Red);
    m_SpiralTree.SetMode(SpiralTreeStarsMode_LeftToRight);
    m_SpiralTree.InitializeTree();

    // Send commit command to apply all the deferred commands.
    DebugPrintf("Committing\n");
    Command* pCommand = (Command *)payloadData;
    memset(pCommand, 0, sizeof(Command));
    payloadSize = sizeof(Command);
    pCommand->type = COMMAND_COMMIT;
    pCommand->address = STRING_GROUP_ALL;
    pCommand->option = COMMAND_OPTION_GROUP_A;
    SendCommand();

    return true;
}

uint32_t ControllerProgramCandyCane::Do()
{
    return m_SpiralTree.Do();
}


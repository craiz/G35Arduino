#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_CONTROLLER_HOLLY
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <ControllerProgramHolly.h>
#include <ColorNodeCommands.h>
#include <ColorNodeSendCommand.h>
#include <LightProgram.h>
#include <ColorUtils.h>
#include <G35String.h>
#include <SequenceUtils.h>
#include <MEORandomStrobe.h>



/*
    This program will color the windows and roof lines to have a holly berry (red) and two leaves (green) at each corner.
*/


ControllerProgramHolly::ControllerProgramHolly(G35& g35)
  : LightProgram(g35)
{
    DebugPrintf("ControllerProgramHolly\n");
}

bool ControllerProgramHolly::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    // setup colors
    COLOR_INFO colorInfo;
    byte encodedRed;
    byte encodedGreen;
    byte encodedWhite;

    colorInfo.palete = COLOR_PALETE_ALL;
    colorInfo.index = 2;
    encodedRed = EncodeColorInfo(&colorInfo);

    colorInfo.palete = COLOR_PALETE_ALL;
    colorInfo.index = 11;
    encodedWhite = EncodeColorInfo(&colorInfo);

    colorInfo.palete = COLOR_PALETE_ALL;
    colorInfo.index = 3;
    encodedGreen = EncodeColorInfo(&colorInfo);

    // Setup parameters common to all raw commands
    memset(payloadData, 0, MAX_COMMAND_BUFFER);
    RawCommand *rawCommand = (RawCommand *)payloadData;
    byte* bulb_data = (byte *)(payloadData + sizeof(RawCommand));
    rawCommand->command.type = COMMAND_RAW;
    rawCommand->command.layout = STRING_LAYOUT_LINEAR;
    rawCommand->bulb_delay = 30;
    rawCommand->intensity = G35::MAX_INTENSITY;

    DebugPrintf("Configuring bonus room window\n");
    payloadSize = sizeof(RawCommand) + 36;
    rawCommand->command.address = STRING_ID_WINDOW_BONUS;
    rawCommand->command.option = COMMAND_OPTION_DEFER;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 35;
    memset(bulb_data, encodedWhite, 36);
    bulb_data[0] = encodedRed;
    bulb_data[1] = encodedGreen;
    bulb_data[6] = encodedGreen;
    bulb_data[7] = encodedRed;
    bulb_data[8] = encodedGreen;
    bulb_data[17] = encodedGreen;
    bulb_data[18] = encodedRed;
    bulb_data[19] = encodedGreen;
    bulb_data[24] = encodedGreen;
    bulb_data[25] = encodedRed;
    bulb_data[26] = encodedGreen;
    bulb_data[35] = encodedGreen;
    SendCommand();

    DebugPrintf("Configuring garage roof left\n");
    payloadSize = sizeof(RawCommand) + 50;
    rawCommand->command.address = STRING_ID_ROOF_GARAGE_LEFT;
    rawCommand->command.option = COMMAND_OPTION_DEFER;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 49;
    memset(bulb_data, encodedWhite, 50);
    bulb_data[31] = encodedGreen;
    bulb_data[32] = encodedRed;
    bulb_data[33] = encodedGreen;
    SendCommand();

    DebugPrintf("Configuring garage roof right\n");
    payloadSize = sizeof(RawCommand) + 50;
    rawCommand->command.address = STRING_ID_ROOF_GARAGE_RIGHT;
    rawCommand->command.option = COMMAND_OPTION_DEFER;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 49;
    memset(bulb_data, encodedWhite, 50);
    bulb_data[1] = encodedGreen;
    bulb_data[2] = encodedRed;
    bulb_data[3] = encodedGreen;
    bulb_data[27] = encodedGreen;
    bulb_data[28] = encodedRed;
    bulb_data[29] = encodedGreen;
    SendCommand();

    DebugPrintf("Configuring bonus room roof left\n");
    payloadSize = sizeof(RawCommand) + 50;
    rawCommand->command.address = STRING_ID_ROOF_BONUS_LEFT;
    rawCommand->command.option = COMMAND_OPTION_DEFER;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 49;
    memset(bulb_data, encodedWhite, 50);
    bulb_data[24] = encodedGreen;
    bulb_data[25] = encodedRed;
    bulb_data[26] = encodedGreen;
    bulb_data[43] = encodedGreen;
    bulb_data[44] = encodedRed;
    bulb_data[45] = encodedGreen;
    SendCommand();

    DebugPrintf("Configuring bonus room roof right\n");
    payloadSize = sizeof(RawCommand) + 36;
    rawCommand->command.address = STRING_ID_ROOF_BONUS_RIGHT;
    rawCommand->command.option = COMMAND_OPTION_DEFER;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 35;
    memset(bulb_data, encodedWhite, 36);
    bulb_data[3] = encodedGreen;
    bulb_data[4] = encodedRed;
    bulb_data[5] = encodedGreen;
    bulb_data[16] = encodedGreen;
    bulb_data[17] = encodedRed;
    bulb_data[18] = encodedGreen;
    bulb_data[23] = encodedGreen;
    bulb_data[24] = encodedRed;
    bulb_data[25] = encodedGreen;
    SendCommand();

    DebugPrintf("Configuring garage door small\n");
    payloadSize = sizeof(RawCommand) + 36;
    rawCommand->command.address = STRING_ID_DOOR_SMALL;
    rawCommand->command.option = COMMAND_OPTION_DEFER;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 35;
    memset(bulb_data, encodedWhite, 36);
    bulb_data[10] = encodedGreen;
    bulb_data[11] = encodedRed;
    bulb_data[12] = encodedGreen;
    bulb_data[23] = encodedGreen;
    bulb_data[24] = encodedRed;
    bulb_data[25] = encodedGreen;
    SendCommand();

    DebugPrintf("Configuring garage door big\n");
    payloadSize = sizeof(RawCommand) + 50;
    rawCommand->command.address = STRING_ID_DOOR_BIG;
    rawCommand->command.option = COMMAND_OPTION_DEFER;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 49;
    memset(bulb_data, encodedWhite, 50);
    bulb_data[10] = encodedGreen;
    bulb_data[11] = encodedRed;
    bulb_data[12] = encodedGreen;
    bulb_data[37] = encodedGreen;
    bulb_data[38] = encodedRed;
    bulb_data[39] = encodedGreen;
    SendCommand();

    DebugPrintf("Configuring living room roof\n");
    payloadSize = sizeof(RawCommand) + 50;
    rawCommand->command.address = STRING_ID_ROOF_LIVING;
    rawCommand->command.option = COMMAND_OPTION_DEFER;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 49;
    memset(bulb_data, encodedWhite, 50);
    bulb_data[10] = encodedGreen;
    bulb_data[11] = encodedRed;
    bulb_data[12] = encodedGreen;
    bulb_data[40] = encodedGreen;
    bulb_data[41] = encodedRed;
    bulb_data[42] = encodedGreen;
    SendCommand();

    DebugPrintf("Configuring living room window\n");
    payloadSize = sizeof(RawCommand) + 50;
    rawCommand->command.address = STRING_ID_WINDOW_LIVING;
    rawCommand->command.option = COMMAND_OPTION_DEFER;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 49;
    memset(bulb_data, encodedWhite, 50);
    bulb_data[0] = encodedRed;
    bulb_data[1] = encodedGreen;
    bulb_data[12] = encodedGreen;
    bulb_data[13] = encodedRed;
    bulb_data[14] = encodedGreen;
    bulb_data[24] = encodedGreen;
    bulb_data[25] = encodedRed;
    bulb_data[26] = encodedGreen;
    bulb_data[37] = encodedGreen;
    bulb_data[38] = encodedRed;
    bulb_data[39] = encodedGreen;
    bulb_data[49] = encodedGreen;
    SendCommand();

    // Front Door
    // Red with white corners
    DebugPrintf("Configuring front door\n");
    payloadSize = sizeof(RawCommand) + 50;
    rawCommand->command.address = STRING_ID_DOOR_FRONT;
    rawCommand->command.option = COMMAND_OPTION_DEFER;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 49;
    memset(bulb_data, encodedWhite, 50);
    bulb_data[19] = encodedGreen;
    bulb_data[20] = encodedRed;
    bulb_data[21] = encodedGreen;
    bulb_data[28] = encodedGreen;
    bulb_data[29] = encodedRed;
    bulb_data[30] = encodedGreen;
    SendCommand();

    DebugPrintf("Configuring star\n");
    payloadSize = sizeof(RawCommand) + 50;
    rawCommand->command.address = STRING_ID_STAR;
    rawCommand->command.option = COMMAND_OPTION_DEFER;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 49;
    memset(bulb_data, encodedWhite, 50);
    bulb_data[49] = encodedGreen;
    bulb_data[0] = encodedRed;
    bulb_data[1] = encodedGreen;
    bulb_data[4] = encodedGreen;
    bulb_data[5] = encodedRed;
    bulb_data[6] = encodedGreen;
    bulb_data[9] = encodedGreen;
    bulb_data[10] = encodedRed;
    bulb_data[11] = encodedGreen;
    bulb_data[14] = encodedGreen;
    bulb_data[15] = encodedRed;
    bulb_data[16] = encodedGreen;
    bulb_data[19] = encodedGreen;
    bulb_data[20] = encodedRed;
    bulb_data[21] = encodedGreen;
    bulb_data[24] = encodedGreen;
    bulb_data[25] = encodedRed;
    bulb_data[26] = encodedGreen;    
    bulb_data[29] = encodedGreen;
    bulb_data[30] = encodedRed;
    bulb_data[31] = encodedGreen;
    bulb_data[34] = encodedGreen;
    bulb_data[35] = encodedRed;
    bulb_data[36] = encodedGreen;
    bulb_data[39] = encodedGreen;
    bulb_data[40] = encodedRed;
    bulb_data[41] = encodedGreen;
    bulb_data[44] = encodedGreen;
    bulb_data[45] = encodedRed;
    bulb_data[46] = encodedGreen;
    SendCommand();

    // Snowflake Big
    DebugPrintf("Configuring snowflake big\n");
    payloadSize = sizeof(RawCommand) + 49;
    rawCommand->command.address = STRING_GROUP_ALL;
    rawCommand->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_C;
    rawCommand->command.layout = STRING_LAYOUT_SNOWFLAKE_REDUCED;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 48;
    memset(bulb_data, encodedWhite, 49);
    bulb_data[0] = encodedRed;
    bulb_data[1] = encodedGreen;
    bulb_data[9] = encodedGreen;
    bulb_data[17] = encodedGreen;
    bulb_data[25] = encodedGreen;
    bulb_data[33] = encodedGreen;
    bulb_data[41] = encodedGreen;

    bulb_data[5] = encodedGreen;
    bulb_data[6] = encodedRed;
    bulb_data[7] = encodedGreen;
    bulb_data[8] = encodedRed;

    bulb_data[13] = encodedGreen;
    bulb_data[14] = encodedRed;
    bulb_data[15] = encodedGreen;
    bulb_data[16] = encodedRed;

    bulb_data[21] = encodedGreen;
    bulb_data[22] = encodedRed;
    bulb_data[23] = encodedGreen;
    bulb_data[24] = encodedRed;

    bulb_data[29] = encodedGreen;
    bulb_data[30] = encodedRed;
    bulb_data[31] = encodedGreen;
    bulb_data[32] = encodedRed;
    
    bulb_data[37] = encodedGreen;
    bulb_data[38] = encodedRed;
    bulb_data[39] = encodedGreen;
    bulb_data[40] = encodedRed;
    
    bulb_data[45] = encodedGreen;
    bulb_data[46] = encodedRed;
    bulb_data[47] = encodedGreen;
    bulb_data[48] = encodedRed;

    SendCommand();

    // Yard
    // Slow christmas sequence chase
    DebugPrintf("Configuring yard\n");
    ProgramCommand* pProgram = (ProgramCommand *)payloadData;
    payloadSize = sizeof(ProgramCommand);
    memset(pProgram, 0, sizeof(ProgramCommand));
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.address = STRING_GROUP_A_YARD | STRING_GROUP_A_BUSHES;
    pProgram->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_A;
    pProgram->command.layout = STRING_LAYOUT_LINEAR;
    pProgram->option = PROGRAM_OPTION_IMMEDIATE | PROGRAM_OPTION_FORWARD;
    pProgram->program = COLOR_NODE_PROGRAM_CHASE;
    pProgram->delay = 1000;

    // Set up the extra data needed for the chase program.
    uint8_t extraDataSize = SetupControllerSequence(pProgram, SEQUENCE_PATTERN_CHRISTMAS);
    payloadSize += extraDataSize;
    SendCommand();

    // Tree Top
    // RandomStrobe Yellow/White
    DebugPrintf("Configuring tree top\n");
    memset(pProgram, 0, payloadSize);
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.address = STRING_ID_TREE_TOP;
    pProgram->command.option = COMMAND_OPTION_DEFER;
    pProgram->command.layout = STRING_LAYOUT_LINEAR;
    pProgram->command.seed = RANDOM_SEED_RESET;
    pProgram->delay = 200;
    pProgram->option  = (2 << 4) | PROGRAM_OPTION_RANDOM;
    pProgram->program = COLOR_NODE_PROGRAM_RANDOM_STROBE;
    pProgram->pattern = RANDOM_STROBE_PATTERN_YELLOW_WHITE;
    SendCommand();

    // Tree
    // Spiral chistmas colors zigzag
    DebugPrintf("Configuring tree\n");
    m_SpiralTree.SetWhiteTip(true);
    m_SpiralTree.SetDelay(100);
    m_SpiralTree.SetDefer(true);
    m_SpiralTree.SetStarGap(0);
    m_SpiralTree.SetStarSize(15);
    m_SpiralTree.SetColors(SpiralTreeStarsColors_RedGreen);
    m_SpiralTree.SetMode(SpiralTreeStarsMode_ZigZag);
    m_SpiralTree.InitializeTree();

    // Send commit command to apply all the commands.
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

uint32_t ControllerProgramHolly::Do()
{
    return m_SpiralTree.Do();
}


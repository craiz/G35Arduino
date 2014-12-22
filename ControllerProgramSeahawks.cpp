#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_CONTROLLER_SEAHAWKS
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <ControllerProgramSeahawks.h>
#include <ColorNodeCommands.h>
#include <ColorNodeSendCommand.h>
#include <LightProgram.h>
#include <ColorUtils.h>
#include <G35String.h>
#include <SequenceUtils.h>


/*
    This program will color the house in Seahawks colors (Blue/Green).
*/


ControllerProgramSeahawks::ControllerProgramSeahawks(G35& g35)
  : LightProgram(g35)
{
    DebugPrintf("ControllerProgramSeahawks\n");
}

bool ControllerProgramSeahawks::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    uint8_t extraDataSize;
    ProgramCommand* pProgram;

    // setup colors
    COLOR_INFO colorInfo;
    byte encodedBlue;
    byte encodedGreen;
    byte encodedWhite;

    colorInfo.palete = COLOR_PALETE_ALL;
    colorInfo.index = 4;
    encodedBlue = EncodeColorInfo(&colorInfo);

    colorInfo.palete = COLOR_PALETE_ALL;
    colorInfo.index = 3;
    encodedGreen = EncodeColorInfo(&colorInfo);

    colorInfo.palete = COLOR_PALETE_ALL;
    colorInfo.index = 0;
    encodedWhite = EncodeColorInfo(&colorInfo);

    // Setup parameters common to all light strings
    memset(payloadData, 0, MAX_COMMAND_BUFFER);
    RawCommand *rawCommand = (RawCommand *)payloadData;
    byte* bulb_data = (byte *)(payloadData + sizeof(RawCommand));
    rawCommand->command.type = COMMAND_RAW;
    rawCommand->command.layout = STRING_LAYOUT_LINEAR;
    rawCommand->bulb_delay = 30;
    rawCommand->intensity = G35::MAX_INTENSITY;

    // Green: Windows, Star, bushes
    DebugPrintf("Configuring Green\n");
    payloadSize = sizeof(RawCommand) + 50;
    rawCommand->command.address = STRING_GROUP_A_WINDOW | STRING_GROUP_A_PROP | STRING_GROUP_A_BUSHES;
    rawCommand->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_A;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 49;
    memset(bulb_data, encodedGreen, 50);
    SendCommand();

    // Green: Tree top
    payloadSize = sizeof(RawCommand) + 35;
    rawCommand->command.address = STRING_ID_TREE_TOP;
    rawCommand->command.option = COMMAND_OPTION_DEFER;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 35;
    memset(bulb_data, encodedGreen, 35);
    SendCommand();

    // Blue: Doors
    DebugPrintf("Configuring Blue\n");
    payloadSize = sizeof(RawCommand) + 50;
    rawCommand->command.address = STRING_GROUP_A_DOOR;
    rawCommand->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_A;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 49;
    memset(bulb_data, encodedBlue, 50);
    SendCommand();

    // Blue and Green: Snowflake
    DebugPrintf("Configuring Snowflake Blue and Green\n");
    payloadSize = sizeof(RawCommand) + 49;
    rawCommand->command.address = STRING_ID_SNOWFLAKE;
    rawCommand->command.option = COMMAND_OPTION_DEFER;
    rawCommand->command.layout = STRING_LAYOUT_SNOWFLAKE_REDUCED;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 48;
    memset(bulb_data, encodedBlue, 49);

    bulb_data[0] = encodedGreen;
    
    bulb_data[5] = encodedGreen;
    bulb_data[6] = encodedGreen;
    bulb_data[7] = encodedGreen;
    bulb_data[8] = encodedGreen;

    bulb_data[13] = encodedGreen;
    bulb_data[14] = encodedGreen;
    bulb_data[15] = encodedGreen;
    bulb_data[16] = encodedGreen;

    bulb_data[21] = encodedGreen;
    bulb_data[22] = encodedGreen;
    bulb_data[23] = encodedGreen;
    bulb_data[24] = encodedGreen;

    bulb_data[29] = encodedGreen;
    bulb_data[30] = encodedGreen;
    bulb_data[31] = encodedGreen;
    bulb_data[32] = encodedGreen;
    
    bulb_data[37] = encodedGreen;
    bulb_data[38] = encodedGreen;
    bulb_data[39] = encodedGreen;
    bulb_data[40] = encodedGreen;
    
    bulb_data[45] = encodedGreen;
    bulb_data[46] = encodedGreen;
    bulb_data[47] = encodedGreen;
    bulb_data[48] = encodedGreen;
    SendCommand();

    // TODO: Fix snowflake grouping.
    rawCommand->command.address = STRING_ID_SNOWFLAKE_2;
    SendCommand();

    uint8_t twelveBase = 2;

    // Tree: Blue with white "12"
    DebugPrintf("Configuring Tree\n");
    payloadSize = sizeof(RawCommand) + 36;
    rawCommand->command.address = STRING_GROUP_B_TREE_1 | STRING_GROUP_B_TREE_2 | STRING_GROUP_B_TREE_5 | STRING_GROUP_B_TREE_6 | STRING_GROUP_B_TREE_13 | STRING_GROUP_B_TREE_14;
    rawCommand->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_B;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 35;
    memset(bulb_data, encodedBlue, 36);
    SendCommand();

    rawCommand->command.address = STRING_GROUP_B_TREE_3 | STRING_GROUP_B_TREE_4;
    rawCommand->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_B;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 35;
    memset(bulb_data, encodedBlue, 36);
    bulb_data[twelveBase + 0] = encodedWhite;
    bulb_data[twelveBase + 1] = encodedWhite;
    bulb_data[twelveBase + 2] = encodedWhite;
    bulb_data[twelveBase + 3] = encodedWhite;
    bulb_data[twelveBase + 4] = encodedWhite;
    bulb_data[twelveBase + 5] = encodedWhite;
    bulb_data[twelveBase + 6] = encodedWhite;
    bulb_data[twelveBase + 7] = encodedWhite;
    bulb_data[twelveBase + 8] = encodedWhite;
    bulb_data[twelveBase + 9] = encodedWhite;
    bulb_data[twelveBase + 10] = encodedWhite;
    bulb_data[twelveBase + 11] = encodedWhite;
    bulb_data[twelveBase + 12] = encodedWhite;
    bulb_data[twelveBase + 13] = encodedWhite;
    SendCommand();

    rawCommand->command.address = STRING_GROUP_B_TREE_7 | STRING_GROUP_B_TREE_8;
    rawCommand->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_B;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 35;
    memset(bulb_data, encodedBlue, 36);
    bulb_data[twelveBase + 0] = encodedWhite;
    bulb_data[twelveBase + 1] = encodedWhite;
    bulb_data[twelveBase + 6] = encodedWhite;
    bulb_data[twelveBase + 7] = encodedWhite;
    bulb_data[twelveBase + 8] = encodedWhite;
    bulb_data[twelveBase + 9] = encodedWhite;
    bulb_data[twelveBase + 10] = encodedWhite;
    bulb_data[twelveBase + 11] = encodedWhite;
    bulb_data[twelveBase + 12] = encodedWhite;
    bulb_data[twelveBase + 13] = encodedWhite;
    SendCommand();

    rawCommand->command.address = STRING_GROUP_B_TREE_9 | STRING_GROUP_B_TREE_10;
    rawCommand->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_B;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 35;
    memset(bulb_data, encodedBlue, 36);
    bulb_data[twelveBase + 0] = encodedWhite;
    bulb_data[twelveBase + 1] = encodedWhite;
    bulb_data[twelveBase + 6] = encodedWhite;
    bulb_data[twelveBase + 7] = encodedWhite;
    bulb_data[twelveBase + 12] = encodedWhite;
    bulb_data[twelveBase + 13] = encodedWhite;
    SendCommand();

    rawCommand->command.address = STRING_GROUP_B_TREE_11 | STRING_GROUP_B_TREE_12;
    rawCommand->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_B;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 35;
    memset(bulb_data, encodedBlue, 36);
    bulb_data[twelveBase + 0] = encodedWhite;
    bulb_data[twelveBase + 1] = encodedWhite;
    bulb_data[twelveBase + 2] = encodedWhite;
    bulb_data[twelveBase + 3] = encodedWhite;
    bulb_data[twelveBase + 4] = encodedWhite;
    bulb_data[twelveBase + 5] = encodedWhite;
    bulb_data[twelveBase + 6] = encodedWhite;
    bulb_data[twelveBase + 7] = encodedWhite;
    bulb_data[twelveBase + 12] = encodedWhite;
    bulb_data[twelveBase + 13] = encodedWhite;
    SendCommand();

    // Blue/Green Chase: Roof, Yard
    DebugPrintf("Configuring Blue/Green Chase\n");
    pProgram = (ProgramCommand *)payloadData;
    payloadSize = sizeof(ProgramCommand);
    memset(pProgram, 0, sizeof(ProgramCommand));
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.address = STRING_GROUP_A_YARD | STRING_GROUP_A_ROOF;
    pProgram->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_A;
    pProgram->command.layout = STRING_LAYOUT_LINEAR;
    pProgram->option = PROGRAM_OPTION_IMMEDIATE | PROGRAM_OPTION_FORWARD;
    pProgram->program = COLOR_NODE_PROGRAM_CHASE;
    pProgram->delay = 500;

    // Set up the extra data needed for the chase program.
    extraDataSize = SetupControllerSequence(pProgram, SEQUENCE_PATTERN_SEAHAWKS_LONG);
    payloadSize += extraDataSize;

    SendCommand();

    // Send commit command to apply all the commands.
    DebugPrintf("Committing\n");
    Command* pCommand = (Command *)payloadData;
    payloadSize = sizeof(Command);
    memset(pCommand, 0, sizeof(Command));
    pCommand->type = COMMAND_COMMIT;
    pCommand->address = STRING_GROUP_ALL;
    pCommand->option = COMMAND_OPTION_GROUP_A;
    SendCommand();

    return true;
}



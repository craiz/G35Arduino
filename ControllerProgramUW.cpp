#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_CONTROLLER_UW
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <ControllerProgramUW.h>
#include <ColorNodeCommands.h>
#include <ColorNodeSendCommand.h>
#include <LightProgram.h>
#include <ColorUtils.h>
#include <G35String.h>
#include <SequenceUtils.h>


/*
    This program will color the house in UW colors (Purple/Yellow).
*/


ControllerProgramUW::ControllerProgramUW(G35& g35)
  : LightProgram(g35)
{
    DebugPrintf("ControllerProgramUW\n");
}

bool ControllerProgramUW::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    // setup colors
    COLOR_INFO colorInfo;
    byte encodedYellow;
    byte encodedPurple;

    colorInfo.palete = COLOR_PALETE_ALL;
    colorInfo.index = 7;
    encodedYellow = EncodeColorInfo(&colorInfo);

    colorInfo.palete = COLOR_PALETE_ALL;
    colorInfo.index = 12;
    encodedPurple = EncodeColorInfo(&colorInfo);

    // Setup parameters common to all light strings
    memset(payloadData, 0, MAX_COMMAND_BUFFER);
    RawCommand *rawCommand = (RawCommand *)payloadData;
    byte* bulb_data = (byte *)(payloadData + sizeof(RawCommand));
    rawCommand->command.type = COMMAND_RAW;
    rawCommand->command.layout = STRING_LAYOUT_LINEAR;
    rawCommand->bulb_delay = 30;
    rawCommand->intensity = G35::MAX_INTENSITY;

    // Yellow: Windows, Doors
    DebugPrintf("Configuring Yellow\n");
    payloadSize = sizeof(RawCommand) + 50;
    rawCommand->command.address = STRING_GROUP_A_WINDOW | STRING_GROUP_A_DOOR;
    rawCommand->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_A;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 49;
    memset(bulb_data, encodedYellow, 50);
    SendCommand();

    // Purple: Tree, Star
    DebugPrintf("Configuring Purple\n");
    payloadSize = sizeof(RawCommand) + 50;
    rawCommand->command.address = STRING_GROUP_A_TREE | STRING_GROUP_A_MISC;
    rawCommand->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_A;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 49;
    memset(bulb_data, encodedPurple, 50);
    SendCommand();

    // Yellow: Tree top
    payloadSize = sizeof(RawCommand) + 35;
    rawCommand->command.address = STRING_ID_TREE_TOP;
    rawCommand->command.option = COMMAND_OPTION_DEFER;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = 34;
    memset(bulb_data, encodedYellow, 35);
    SendCommand();

    // Purple/Yellow Chase: Roof, Yard
    DebugPrintf("Configuring Purple/Yellow Chase\n");
    ProgramCommand* pProgram = (ProgramCommand *)payloadData;
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
    uint8_t extraDataSize = SetupControllerSequence(pProgram, SEQUENCE_PATTERN_UW);
    payloadSize += extraDataSize;

    SendCommand();    

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



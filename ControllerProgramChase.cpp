#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_CONTROLLER_CHASE
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <ControllerProgramChase.h>
#include <ColorNodeCommands.h>
#include <ColorNodeSendCommand.h>
#include <LightProgram.h>
#include <SequenceUtils.h>
#include <G35String.h>


ControllerProgramChase::ControllerProgramChase(G35& g35, pattern_t pattern)
  : LightProgram(g35)
{
    DebugPrintf("ControllerProgramChase\n");

    pattern_ = pattern;
}

bool ControllerProgramChase::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    // Default is all strings go forward.
    DebugPrintf("Initializing strings...\n");
    ProgramCommand* pProgram = (ProgramCommand *)payloadData;
    payloadSize = sizeof(ProgramCommand);
    memset(pProgram, 0, sizeof(ProgramCommand));
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.address = STRING_GROUP_ALL & (~STRING_GROUP_A_TREE);
    pProgram->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_A;
    pProgram->command.layout = STRING_LAYOUT_LINEAR;
    pProgram->option = PROGRAM_OPTION_INCREMENTAL | PROGRAM_OPTION_FORWARD;
    pProgram->program = COLOR_NODE_PROGRAM_CHASE;
    pProgram->delay = 100;

    // Set up the extra data needed for the chase program.
    uint8_t extraDataSize = SetupControllerSequence(pProgram, pattern_);
    payloadSize += extraDataSize;

    SendCommand();

    // Windows go backward.
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.address = STRING_GROUP_A_WINDOW;
    pProgram->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_A;
    pProgram->option = PROGRAM_OPTION_INCREMENTAL | PROGRAM_OPTION_BACKWARD;
    SendCommand();

    // Odd tree legs go backward.
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.address = STRING_GROUP_B_TREE_1 | STRING_GROUP_B_TREE_3 | STRING_GROUP_B_TREE_5 | STRING_GROUP_B_TREE_7 | STRING_GROUP_B_TREE_9 | STRING_GROUP_B_TREE_11 | STRING_GROUP_B_TREE_13;
    pProgram->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_B;
    pProgram->option = PROGRAM_OPTION_INCREMENTAL | PROGRAM_OPTION_BACKWARD;
    SendCommand();

    // Even tree legs go forward.
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.address = STRING_GROUP_B_TREE_2 | STRING_GROUP_B_TREE_4 | STRING_GROUP_B_TREE_6 | STRING_GROUP_B_TREE_8 | STRING_GROUP_B_TREE_10 | STRING_GROUP_B_TREE_12 | STRING_GROUP_B_TREE_14;
    pProgram->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_B;
    pProgram->option = PROGRAM_OPTION_INCREMENTAL | PROGRAM_OPTION_FORWARD;
    SendCommand();

    // Star goes forward using rings layout
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.address = STRING_ID_STAR;
    pProgram->command.option = COMMAND_OPTION_DEFER;
    pProgram->command.layout = STRING_LAYOUT_STAR_RINGS;
    pProgram->delay = 200;
    pProgram->option = PROGRAM_OPTION_INCREMENTAL | PROGRAM_OPTION_FORWARD;
    SendCommand();

    // Tree top does horizontal lines center
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.address = STRING_ID_TREE_TOP;
    pProgram->command.option = COMMAND_OPTION_DEFER;
    pProgram->command.layout = STRING_LAYOUT_HORIZONTAL_LINES_CENTER;
    pProgram->option = PROGRAM_OPTION_INCREMENTAL | PROGRAM_OPTION_FORWARD;
    SendCommand();

    // Send commit command to apply all the commands.
    DebugPrintf("Committing all\n");
    Command* pCommand = (Command *)payloadData;
    memset(pCommand, 0, sizeof(Command));
    payloadSize = sizeof(Command);
    pCommand->type = COMMAND_COMMIT;
    pCommand->address = STRING_GROUP_ALL;
    pCommand->option = COMMAND_OPTION_GROUP_A | COMMAND_OPTION_GROUP_B;
    SendCommand();

    return true;
}


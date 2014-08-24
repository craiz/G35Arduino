#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_CONTROLLER_STROBE
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <ControllerProgramStrobe.h>
#include <ColorNodeCommands.h>
#include <ColorNodeSendCommand.h>
#include <LightProgram.h>
#include <MEORandomStrobe.h>
#include <ColorNodeUtils.h>
#include <G35String.h>



ControllerProgramStrobe::ControllerProgramStrobe(G35& g35, pattern_t pattern)
  : LightProgram(g35)
{
    DebugPrintf("ControllerProgramStrobe\n");

    pattern_ = pattern;
}

bool ControllerProgramStrobe::Initialize(pattern_t pattern, uint8_t option, delay_t delay)
{
    DebugPrintf("Initializing strings...\n");

    ProgramCommand* pProgram = (ProgramCommand *)payloadData;

    // First turn off all the lights
    DebugPrintf("All off...\n");
    payloadSize = sizeof(ProgramCommand);
    memset(pProgram, 0, payloadSize);
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.address = STRING_GROUP_ALL;
    pProgram->command.option = COMMAND_OPTION_GROUP_A;
    pProgram->delay = 5;
    pProgram->program = COLOR_NODE_PROGRAM_SWITCH_OFF;
    pProgram->pattern = 1; // Soft Off

    SendCommand(SEND_COMMAND_RETRIES_DEFAULT * 2, SEND_COMMAND_RETRY_DELAY_DEFAULT);

    sleep(1000);

#if CURRENT_CONTROLLER_CONFIGURATION == CHRISTMAS

    // Then do a stobe fill
    DebugPrintf("Strobe fill...\n");
    payloadSize = sizeof(ProgramCommand);
    memset(pProgram, 0, payloadSize);
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->program = COLOR_NODE_PROGRAM_STROBE_FILL;
    pProgram->delay = DELAY_DEFAULT;
    pProgram->pattern = 0;

    // Parameters:
    // -----------
    // Background Color (16-bit)    = ProgramCommand + 0
    // Fill Color (16-bit)          = ProgramCommand + 2
    // Strobe Color (16-bit)        = ProgramCommand + 4
    // Strobe Wait                  = pattern (if 0, no strobe)

    uint8_t * extraData = (uint8_t *)pProgram + sizeof(ProgramCommand);
    color_t * colors = (color_t *)&extraData[0];

    colors[0] = COLOR_BLACK;
    switch (pattern_)
    {
    case RANDOM_STROBE_PATTERN_BLUE_WHITE:
        colors[1] = COLOR(0,0,4);
        break;
    case RANDOM_STROBE_PATTERN_RED_WHITE:
        colors[1] = COLOR(4,0,0);
        break;
    case RANDOM_STROBE_PATTERN_GREEN_WHITE:
        colors[1] = COLOR(0,4,0);
        break;
    }
    colors[2] = COLOR_WHITE;

    payloadSize += 6;

    // Doors, windows and do horizontal lines backward (top to bottom)
    pProgram->command.address = STRING_GROUP_A_WINDOW | STRING_GROUP_A_DOOR | STRING_GROUP_A_MISC;
    pProgram->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_A;
    pProgram->command.layout = STRING_LAYOUT_HORIZONTAL_LINES;
    pProgram->option = PROGRAM_OPTION_INCREMENTAL | PROGRAM_OPTION_BACKWARD;
    SendCommand();

    // Star does horizontal lines forward (top to bottom)
    // TODO: PAUL: Fix Star horizontal lines to be bottom up like all other strings layouts
    pProgram->command.address = STRING_ID_STAR;
    pProgram->command.option = COMMAND_OPTION_DEFER;
    pProgram->command.layout = STRING_LAYOUT_HORIZONTAL_LINES;
    pProgram->option = PROGRAM_OPTION_INCREMENTAL | PROGRAM_OPTION_FORWARD;
    SendCommand();

    // Tree, roof and yard do linear forward.
    pProgram->command.address = STRING_GROUP_A_TREE | STRING_GROUP_A_ROOF | STRING_GROUP_A_YARD;
    pProgram->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_A;
    pProgram->command.layout = STRING_LAYOUT_LINEAR;
    pProgram->option = PROGRAM_OPTION_INCREMENTAL | PROGRAM_OPTION_FORWARD;
    SendCommand();

    // Tree top does horizontal lines backward (top to bottom)
    pProgram->command.address = STRING_ID_TREE_TOP;
    pProgram->command.option = COMMAND_OPTION_DEFER;
    pProgram->command.layout = STRING_LAYOUT_HORIZONTAL_LINES;
    pProgram->option = PROGRAM_OPTION_INCREMENTAL | PROGRAM_OPTION_BACKWARD;
    SendCommand();

    // Send commit command to apply all the commands.
    DebugPrintf("Committing...\n");
    Command* pCommand = (Command *)payloadData;
    payloadSize = sizeof(Command);
    memset(pCommand, 0, sizeof(Command));
    pCommand->type = COMMAND_COMMIT;
    pCommand->address = STRING_GROUP_ALL;
    pCommand->option = COMMAND_OPTION_GROUP_A;
    SendCommand();

    sleep(1100);
#endif

    // Finally, start the random strobe
    DebugPrintf("Random strobe...\n");
    payloadSize = sizeof(ProgramCommand);
    memset(pProgram, 0, payloadSize);
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.address = STRING_GROUP_ALL;
    pProgram->command.option = COMMAND_OPTION_GROUP_A;
    pProgram->command.layout = STRING_LAYOUT_LINEAR;
    pProgram->command.seed = RANDOM_SEED_RESET;
    pProgram->delay = 500;
    pProgram->option = PROGRAM_OPTION_RANDOM;
    pProgram->program = COLOR_NODE_PROGRAM_RANDOM_STROBE;
    pProgram->pattern = pattern_;

    SendCommand();

    return true;
}


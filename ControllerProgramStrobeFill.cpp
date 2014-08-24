#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_CONTROLLER_STROBE_FILL
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <ControllerProgramStrobeFill.h>
#include <ColorNodeCommands.h>
#include <ColorNodeSendCommand.h>
#include <LightProgram.h>
#include <SequenceUtils.h>
#include <ColorUtils.h>
#include <G35String.h>


ControllerProgramStrobeFill::ControllerProgramStrobeFill(G35& g35)
  : LightProgram(g35)
{
    DebugPrintf("ControllerProgramStrobeFill\n");
}

bool ControllerProgramStrobeFill::Initialize(pattern_t pattern, uint8_t option, delay_t delay)
{
    DebugPrintf("Initializing strings...\n");
    ProgramCommand* pProgram = (ProgramCommand *)payloadData;
    payloadSize = sizeof(ProgramCommand);
    memset(pProgram, 0, sizeof(ProgramCommand));
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.address = STRING_GROUP_ALL & (~STRING_GROUP_A_TREE);
    pProgram->command.option = COMMAND_OPTION_GROUP_A;
    pProgram->command.layout = STRING_LAYOUT_LINEAR;
    pProgram->option = PROGRAM_OPTION_INCREMENTAL | PROGRAM_OPTION_FORWARD;
    pProgram->program = COLOR_NODE_PROGRAM_STROBE_FILL;
    pProgram->delay = 500;
    pProgram->pattern = 0;

    // Set up the extra data needed for the chase program.


    // Parameters:
    // -----------
    // Background Color (16-bit)    = ProgramCommand + 0
    // Fill Color (16-bit)          = ProgramCommand + 2
    // Strobe Color (16-bit)        = ProgramCommand + 4
    // Strobe Wait                  = pattern (if 0, no strobe)

    uint8_t * extraData = (uint8_t *)pProgram + sizeof(ProgramCommand);
    color_t * colors = (color_t *)&extraData[0];

    colors[0] = COLOR_BLACK;
    colors[1] = COLOR_ORANGE;
    colors[2] = COLOR_WHITE;

    payloadSize += 6;

    SendCommand();

    return true;
}


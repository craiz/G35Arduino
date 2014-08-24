#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_CONTROLLER_METEORITE
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <ControllerProgramMeteorite.h>
#include <ColorNodeCommands.h>
#include <ColorNodeSendCommand.h>
#include <LightProgram.h>
#include <G35String.h>


ControllerProgramMeteorite::ControllerProgramMeteorite(G35& g35)
  : LightProgram(g35)
{
    DebugPrintf("ControllerProgramMeteorite\n");
}

bool ControllerProgramMeteorite::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    DebugPrintf("Initializing strings...\n");
    ProgramCommand* command = (ProgramCommand *)payloadData;
    payloadSize = sizeof(ProgramCommand);

    memset(command, 0, sizeof(ProgramCommand));
    command->command.type = COMMAND_PROGRAM;
    command->command.address = STRING_GROUP_ALL;
    command->command.option = COMMAND_OPTION_GROUP_A;
    command->command.layout = STRING_LAYOUT_LINEAR;
    command->delay = DELAY_DEFAULT;
    command->program = COLOR_NODE_PROGRAM_METEORITE;
    SendCommand();

    return true;
}


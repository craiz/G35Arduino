#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_CONTROLLER_ALTERNATE_DIRECTION
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <ControllerProgramCrossOverWave.h>
#include <ColorNodeCommands.h>
#include <ColorNodeUtils.h>
#include <ColorNodeSendCommand.h>
#include <LightProgram.h>
#include <G35String.h>


ControllerProgramCrossOverWave::ControllerProgramCrossOverWave(G35& g35)
  : LightProgram(g35)
{
    DebugPrintf("ControllerProgramCrossOverWave\n");
}

bool ControllerProgramCrossOverWave::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    DebugPrintf("Initializing strings...\n");

    uint16_t seed = rand();
    ProgramCommand* pProgram = (ProgramCommand *)payloadData;
    payloadSize = sizeof(ProgramCommand);
    memset(pProgram, 0, sizeof(ProgramCommand));
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.address = STRING_GROUP_ALL;
    pProgram->command.option = COMMAND_OPTION_GROUP_A;
    pProgram->command.layout = STRING_LAYOUT_RINGS_CENTER;
    pProgram->command.seed = seed;
    pProgram->delay = DELAY_DEFAULT;
    pProgram->option = PROGRAM_OPTION_RANDOM;
    pProgram->program = COLOR_NODE_PROGRAM_CROSS_OVER_WAVE;
    SendCommand();

    return true;
}

uint32_t ControllerProgramCrossOverWave::Do()
{
    return delay_;
}


#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_CONTROLLER_SOLID_RAINBOW
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <ControllerProgramSolidRainbow.h>
#include <ColorNodeCommands.h>
#include <ColorNodeSendCommand.h>
#include <LightProgram.h>
#include <G35String.h>



ControllerProgramSolidRainbow::ControllerProgramSolidRainbow(G35& g35)
  : LightProgram(g35)
{
    DebugPrintf("ControllerProgramSolidRainbow\n");
}

bool ControllerProgramSolidRainbow::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    DebugPrintf("Initializing strings...\n");
    ProgramCommand* program = (ProgramCommand *)payloadData;
    payloadSize = sizeof(ProgramCommand);

    memset(program, 0, sizeof(ProgramCommand));
    program->command.type = COMMAND_PROGRAM;
    program->command.address = STRING_GROUP_ALL;
    program->command.option = COMMAND_OPTION_GROUP_A;
    program->command.layout = STRING_LAYOUT_LINEAR;
    program->delay = DELAY_DEFAULT;
    program->option = PROGRAM_OPTION_FIXED | PROGRAM_OPTION_IMMEDIATE;
    program->program = COLOR_NODE_PROGRAM_SOLID;

    m_colorInfo.palete = COLOR_PALETE_SMOOTH_WHEEL;
    m_colorInfo.index = 0;

    program->pattern = EncodeColorInfo(&m_colorInfo);

    SendCommand();

    delay_ = 42;

    return true;
}

uint32_t ControllerProgramSolidRainbow::Do()
{
    DebugPrintf("Sending Update...\n");
    ProgramCommand* program = (ProgramCommand *)payloadData;
    
    program->command.option = COMMAND_OPTION_UPDATE | COMMAND_OPTION_GROUP_A;

    m_colorInfo.index = (m_colorInfo.index + 1) % GetPaleteMax(m_colorInfo.palete);

    program->pattern = EncodeColorInfo(&m_colorInfo);
    
    SendCommand();

#if 0
    static uint8_t LongSleep = 0;
    
    if (LongSleep == 0)
    {
        LongSleep = 16;
        return 1000;
    }
    else
    {
        LongSleep--;
        return delay_;
    }
#endif
    return delay_;
}


#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_CONTROLLER_DISSOLVE
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <ControllerProgramDissolve.h>
#include <ColorNodeCommands.h>
#include <ColorNodeSendCommand.h>
#include <LightProgram.h>
#include <G35String.h>
#include <WaveUtils.h>
#include <ColorNodeUtils.h>


ControllerProgramDissolve::ControllerProgramDissolve(G35& g35)
  : LightProgram(g35)
{
    DebugPrintf("ControllerProgramDissolve\n");
}

bool ControllerProgramDissolve::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    DebugPrintf("Initializing strings...\n");

    // First turn off all the lights
    DebugPrintf("All off...\n");
    ProgramCommand* pProgram = (ProgramCommand *)payloadData;
    payloadSize = sizeof(ProgramCommand);
    memset(pProgram, 0, payloadSize);
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.address = STRING_GROUP_ALL;
    pProgram->command.option = COMMAND_OPTION_GROUP_A;
    pProgram->command.layout = STRING_LAYOUT_LINEAR;
    pProgram->delay = 5;
    pProgram->program = COLOR_NODE_PROGRAM_SWITCH_OFF;
    pProgram->pattern = 1; // Soft Off

    SendCommand();

    sleep(900);

    // Setup colors for first dissolve in from black.
    m_Color1 = WAVE_COLOR_BLACK;
    m_Color2 = WAVE_COLOR_BLACK;

    delay_ = 5000;

    return true;
}

uint32_t ControllerProgramDissolve::Do()
{
    ProgramCommand *pProgram = (ProgramCommand *)payloadData;
    memset(pProgram, 0, sizeof(ProgramCommand));
    pProgram->command.type= COMMAND_PROGRAM;
    pProgram->command.address = STRING_GROUP_ALL;
    pProgram->command.option = COMMAND_OPTION_GROUP_A;
    pProgram->command.layout = STRING_LAYOUT_LINEAR;
    pProgram->command.seed = RANDOM_SEED_RESET;
    pProgram->program = COLOR_NODE_PROGRAM_DISSOLVE;
    pProgram->delay = 50;
    pProgram->option = PROGRAM_OPTION_FORWARD | PROGRAM_OPTION_IMMEDIATE | PROGRAM_OPTION_RANDOM | PROGRAM_OPTION_WAIT;

    m_Color1 = m_Color2;
    m_Color2 = GetRandomWaveColor(m_Color1, WAVE_COLOR_BLACK, WAVE_COLOR_BLACK);

    pProgram->pattern = ((m_Color2 & 0x7) << 3) | (m_Color1 & 0x7);

    uint8_t * extraData = payloadData + sizeof(ProgramCommand);
    extraData[0] = 0; // min tick rate
    extraData[1] = 5; // max tick rate

    *((delay_t *)&extraData[2]) = 1000;

    payloadSize = sizeof(ProgramCommand) + 4;

    SendCommand();

    return delay_;
}


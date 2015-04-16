#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_CONTROLLER_STEPPED_WAVE
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <ControllerProgramSteppedWave.h>
#include <ColorNodeCommands.h>
#include <ColorNodeSendCommand.h>
#include <WaveUtils.h>
#include <LightProgram.h>
#include <G35String.h>



#define USE_RAINBOW_COLORS 1

#if USE_RAINBOW_COLORS
uint8_t rainbowColors[] = { WAVE_COLOR_RED,
                            WAVE_COLOR_YELLOW,
                            WAVE_COLOR_GREEN,
                            WAVE_COLOR_CYAN,
                            WAVE_COLOR_BLUE, 
                            WAVE_COLOR_MAGENTA};
#endif

#define COUNTOF(_array) (sizeof(_array) / sizeof(*_array))

ControllerProgramSteppedWave::ControllerProgramSteppedWave(G35& g35)
  : LightProgram(g35), m_lastColor(WAVE_COLOR_RED)
{
    DebugPrintf("ControllerProgramSteppedWave\n");
}

bool ControllerProgramSteppedWave::Initialize(pattern_t pattern, uint8_t option, delay_t delay)
{
    DebugPrintf("Initializing strings...\n");

    delay_ = 5000;

    m_lastColor = GetRandomWaveColor(m_lastColor, m_lastColor, WAVE_COLOR_BLACK);

    return true;
}

uint32_t ControllerProgramSteppedWave::Do()
{
    DebugPrintf("Sending Update...\n");

    ProgramCommand *program = (ProgramCommand *)payloadData;
    program->command.type= COMMAND_PROGRAM;
    program->command.address = STRING_GROUP_ALL & (~STRING_GROUP_A_TREE);
    program->command.option = COMMAND_OPTION_GROUP_A;
    program->command.layout = STRING_LAYOUT_LINEAR;
    program->delay = 200;
    program->pattern = 2; // number of colors
    program->option = 15 << 4; // ramp size
    program->option |= PROGRAM_OPTION_FIXED | PROGRAM_OPTION_WAIT;
    program->program = COLOR_NODE_PROGRAM_WAVE;
    
    uint8_t * extraData = payloadData + sizeof(ProgramCommand);
    extraData[0] = 0; // pixel count
    extraData[1] = 0; // pixel distribution
    extraData[2] = 0xFF; // span size, max (all lights)
    uint8_t * colors = &extraData[3];
    uint8_t * holds = colors + program->pattern;
#if USE_RAINBOW_COLORS
    // Rainbow order
    colors[0] = rainbowColors[m_lastColor];
    m_lastColor = (m_lastColor + 1) % COUNTOF(rainbowColors);
    colors[1] = rainbowColors[m_lastColor];
#else 
    // Random order
    colors[0] = m_lastColor;
    m_lastColor = GetRandomWaveColor(m_lastColor, m_lastColor, WAVE_COLOR_BLACK);
    colors[1] = m_lastColor;
#endif
    holds[0] = 1;
    holds[1] = 1;
    
    payloadSize = sizeof(ProgramCommand) + (program->pattern * 2) + 3;

    SendCommand();

    // Tree top
    program->command.address = STRING_ID_TREE_TOP;
    program->command.option = 0;
    SendCommand();

    // Tree legs will transition with a slight delay to create a left -> right effect.
    for (uint8_t i = 0; i < TREE_LEG_COUNT; i++)
    {
        program->command.address = PACK_STRING_GROUP(i + 1);
        program->command.option = COMMAND_OPTION_GROUP_B;
        SendCommand();
        delay(25);
    }

    return delay_;
}


#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_CONTROLLER_FADEIN_FADEOUT
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <ControllerProgramFadeInFadeOut.h>
#include <ColorNodeCommands.h>
#include <ColorNodeSendCommand.h>
#include <LightProgram.h>
#include <ColorUtils.h>
#include <ColorNodeUtils.h>
#include <G35String.h>



ControllerProgramFadeInFadeOut::ControllerProgramFadeInFadeOut(G35& g35)
  : LightProgram(g35)
{
    DebugPrintf("ControllerProgramFadeInFadeOut\n");
}

bool ControllerProgramFadeInFadeOut::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    DebugPrintf("Initializing strings...\n");
    ProgramCommand* pProgram = (ProgramCommand *)payloadData;
    payloadSize = sizeof(ProgramCommand);

    // First turn off all the lights
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

    memset(pProgram, 0, sizeof(ProgramCommand));
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.address = STRING_GROUP_ALL;
    pProgram->command.option = COMMAND_OPTION_GROUP_A;
    pProgram->delay = DELAY_DEFAULT;
    pProgram->option = PROGRAM_OPTION_FIXED | PROGRAM_OPTION_WAIT;
    pProgram->program = COLOR_NODE_PROGRAM_FADE_SINGLE_COLORS;

    // Pick an initial random color; any color but black
    m_colorInfo.palete = COLOR_PALETE_ALL;
#if CURRENT_CONTROLLER_CONFIGURATION == CHRISTMAS
    m_colorInfo.index = GetRandomPaleteColor(m_colorInfo.palete, 1, 1);
#else
    m_colorInfo.index = 2;
#endif
    pProgram->pattern = EncodeColorInfo(&m_colorInfo);

#if CURRENT_CONTROLLER_CONFIGURATION == CHRISTMAS
    delay_ = 5000;
#else
    delay_ = 10000;
    pProgram->delay = 10;
#endif

    SendCommand();

    return true;
}


#if CURRENT_CONTROLLER_CONFIGURATION == HALLOWEEN

uint8_t colors[] = { 0, 2, 3, 7, 9, 10, 12, 14, 15 };
uint8_t color_count = 9;
#endif

uint32_t ControllerProgramFadeInFadeOut::Do()
{
    DebugPrintf("Sending Update...\n");
    ProgramCommand* pProgram = (ProgramCommand *)payloadData;

    pProgram->command.option = COMMAND_OPTION_UPDATE | COMMAND_OPTION_GROUP_A;


#if CURRENT_CONTROLLER_CONFIGURATION == CHRISTMAS
    // Pick a new random color; any color but the previous color or black
    m_colorInfo.index = GetRandomPaleteColor(m_colorInfo.palete, m_colorInfo.index, 1); 
#else
    m_colorInfo.index = colors[rand() % color_count];
#endif

    pProgram->pattern = EncodeColorInfo(&m_colorInfo);

#if DEBUG_ENABLED
    uint8_t r, g, b;
    color_t color = GetPaleteColor(&m_colorInfo);
    r = color & 0x0F;
    g = (color >> 4) & 0x0F;
    b = (color >> 8) & 0x0F;
    
    DebugPrintf("Encoded Color: %u\n", pProgram->pattern);
    DebugPrintf("Palete: %u\n", m_colorInfo.palete);
    DebugPrintf("Index: %u\n", m_colorInfo.index);
    DebugPrintf("Actual Color: %d,%d,%d\n", r, g, b);
#endif

    SendCommand();
  
    return delay_;
}


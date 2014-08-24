#include <DebugConfig.h>
#if DEBUG_SPIRAL_TREE_STARS
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <SpiralTreeStars.h>
#include <ColorNodeCommands.h>
#include <ColorNodeUtils.h>
#include <ColorNodeSendCommand.h>
#include <LightProgram.h>
#include <WaveUtils.h>
#include <G35String.h>


// ZigZag
uint16_t zigzag[] = { STRING_GROUP_B_TREE_7 | STRING_GROUP_B_TREE_8,
                      STRING_GROUP_B_TREE_6 | STRING_GROUP_B_TREE_9,
                      STRING_GROUP_B_TREE_5 | STRING_GROUP_B_TREE_10,
                      STRING_GROUP_B_TREE_4 | STRING_GROUP_B_TREE_11,
                      STRING_GROUP_B_TREE_3 | STRING_GROUP_B_TREE_12,
                      STRING_GROUP_B_TREE_2 | STRING_GROUP_B_TREE_13,
                      STRING_GROUP_B_TREE_1 | STRING_GROUP_B_TREE_14,
                      0,
                      0,
                      STRING_GROUP_B_TREE_1 | STRING_GROUP_B_TREE_14,
                      STRING_GROUP_B_TREE_2 | STRING_GROUP_B_TREE_13,
                      STRING_GROUP_B_TREE_3 | STRING_GROUP_B_TREE_12,
                      STRING_GROUP_B_TREE_4 | STRING_GROUP_B_TREE_11,
                      STRING_GROUP_B_TREE_5 | STRING_GROUP_B_TREE_10,
                      STRING_GROUP_B_TREE_6 | STRING_GROUP_B_TREE_9,
                      STRING_GROUP_B_TREE_7 | STRING_GROUP_B_TREE_8,
                      0,
                      0 };
uint8_t zigzag_count = ARRAYSIZE(zigzag);    


uint8_t blue_colors[] = { WAVE_COLOR_BLUE };
uint8_t blue_colors_size = ARRAYSIZE(blue_colors);

uint8_t red_colors[] = { WAVE_COLOR_RED };
uint8_t red_colors_size = ARRAYSIZE(red_colors);

uint8_t green_colors[] = { WAVE_COLOR_GREEN };
uint8_t green_colors_size = ARRAYSIZE(green_colors);

uint8_t rainbow_colors[] = { WAVE_COLOR_RED,
                             WAVE_COLOR_YELLOW,
                             WAVE_COLOR_GREEN,
                             WAVE_COLOR_CYAN,
                             WAVE_COLOR_BLUE, 
                             WAVE_COLOR_MAGENTA };
uint8_t rainbow_colors_size = ARRAYSIZE(rainbow_colors);

uint8_t redgreen_colors[] = {  WAVE_COLOR_RED,
                               WAVE_COLOR_GREEN };
uint8_t redgreen_colors_size = ARRAYSIZE(redgreen_colors);

uint8_t christmas_colors[] = { WAVE_COLOR_GREEN,
                               WAVE_COLOR_RED,
                               WAVE_COLOR_WHITE };
uint8_t christmas_colors_size = ARRAYSIZE(christmas_colors);


#define TICK_GAP_MIN (0)
#define TICK_GAP_MAX (1)
#define POSITION_GAP_MIN (2)
#define POSITION_GAP_MAX (3)
#define STARS_MAX (4)


SpiralTreeStars::SpiralTreeStars()
{
    DebugPrintf("SpiralTreeStars\n");

    SetStarGap(5);
    SetWhiteTip(false);
    SetDelay(50);
    SetDefer(false);
    SetStarSize(10);
    SetMode(SpiralTreeStarsMode_LeftToRight);
    SetColors(SpiralTreeStarsColors_Blue);

    m_CycleIndex = 0;
    m_ColorIndex = 0;
    m_CyclesUntilNewStar = 0;
    m_CyclesUntilNewColor = 0;
    m_Address = 0;
}

void SpiralTreeStars::SetColors(SpiralTreeStarsColors colors)
{
    switch (colors)
    {
    default:
    case SpiralTreeStarsColors_Blue:
        m_Colors = SpiralTreeStarsColors_Blue;
        m_ColorMap = blue_colors;
        m_ColorMapSize = blue_colors_size;
        break;
    case SpiralTreeStarsColors_Red:
        m_Colors = SpiralTreeStarsColors_Red;
        m_ColorMap = red_colors;
        m_ColorMapSize = red_colors_size;
        break;
    case SpiralTreeStarsColors_Green:
        m_Colors = SpiralTreeStarsColors_Green;
        m_ColorMap = green_colors;
        m_ColorMapSize = green_colors_size;
        break;
    case SpiralTreeStarsColors_Rainbow:
        m_Colors = SpiralTreeStarsColors_Rainbow;
        m_ColorMap = rainbow_colors;
        m_ColorMapSize = rainbow_colors_size;
        break;
    case SpiralTreeStarsColors_RedGreen:
        m_Colors = SpiralTreeStarsColors_RedGreen;
        m_ColorMap = redgreen_colors;
        m_ColorMapSize = redgreen_colors_size;
        break;
    case SpiralTreeStarsColors_Christmas:
        m_Colors = SpiralTreeStarsColors_Christmas;
        m_ColorMap = christmas_colors;
        m_ColorMapSize = christmas_colors_size;
        break;
    }
}

void SpiralTreeStars::SetMode(SpiralTreeStarsMode mode)
{
    switch (mode)
    {
    default:
    case SpiralTreeStarsMode_LeftToRight:
        m_Mode = SpiralTreeStarsMode_LeftToRight;
        m_CycleSize = 14;
        m_ColorCycleSize = m_StarGap;
        m_NewStarAddress = 0x0001;
        break;
    case SpiralTreeStarsMode_RightToLeft:
        m_Mode = SpiralTreeStarsMode_RightToLeft;
        m_CycleSize = 14;
        m_ColorCycleSize = m_StarGap;
        m_NewStarAddress = 0x8000;
        break;
    case SpiralTreeStarsMode_ZigZag:
        m_Mode = SpiralTreeStarsMode_ZigZag;
        m_CycleSize = zigzag_count;
        m_ColorCycleSize = 9;
        m_NewStarAddress = 0;
        break;
    }
}

void SpiralTreeStars::SetWhiteTip(bool white)
{
    m_WhiteTip = white;
}

void SpiralTreeStars::SetStarGap(uint8_t gap)
{
    m_StarGap = gap;
}

void SpiralTreeStars::SetDelay(delay_t delay)
{
    m_Delay = delay;
}

void SpiralTreeStars::SetDefer(bool defer)
{
    m_Defer = defer;
}

void SpiralTreeStars::SetStarSize(uint8_t size)
{
    m_StarSize = size;
}

void SpiralTreeStars::InitializeTree()
{
    memset(payloadData, 0, MAX_COMMAND_BUFFER);
    payloadSize = sizeof(ProgramCommand) + 5;
    ProgramCommand *pProgram = (ProgramCommand *)payloadData;
    byte* extra_data = (byte *)(payloadData + sizeof(ProgramCommand));
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.layout = STRING_LAYOUT_LINEAR;
    pProgram->command.option = COMMAND_OPTION_GROUP_B;
    if (m_Defer)
    {
        pProgram->command.option |= COMMAND_OPTION_DEFER;
    }
    pProgram->command.address = 0xFFFF & ~0xC000; // All tree but trunk and top

    pProgram->program = COLOR_NODE_PROGRAM_SHOOTING_STARS;

    pProgram->option = 2 << 4;
    pProgram->option |= PROGRAM_OPTION_FIXED | PROGRAM_OPTION_WAIT;
    if (m_WhiteTip)
    {
        pProgram->option |= OPTION_BIT_2;
    }
    pProgram->delay = 0;

    pProgram->pattern = WAVE_COLOR_BLUE << 4;
    pProgram->pattern |= m_StarSize;

    extra_data[TICK_GAP_MIN] = 0;
    extra_data[TICK_GAP_MAX] = 0;
    extra_data[POSITION_GAP_MIN] = 0;
    extra_data[POSITION_GAP_MAX] = 0;
    extra_data[STARS_MAX] = 10;

    SendCommand();
}

uint32_t SpiralTreeStars::Do()
{
    // Pick the color
    uint8_t waveColor = m_ColorMap[m_ColorIndex];
    if (m_CyclesUntilNewColor == 0)
    {
        m_ColorIndex = (m_ColorIndex + 1) % m_ColorMapSize;
        m_CyclesUntilNewColor = m_CycleSize;
    }
    else
    {
        m_CyclesUntilNewColor--;
    }

    // Pick the address for this cycle
    switch (m_Mode)
    {
    case SpiralTreeStarsMode_LeftToRight:
        m_Address = m_Address << 1;
        break;
    case SpiralTreeStarsMode_RightToLeft:
        m_Address = m_Address >> 1;
        break;
    case SpiralTreeStarsMode_ZigZag:
        m_Address = zigzag[m_CycleIndex];
        break;
    }

    if (m_CyclesUntilNewStar == 0)
    {
        m_Address |= m_NewStarAddress;
        m_CyclesUntilNewStar = m_StarGap;
    }
    else
    {
        m_CyclesUntilNewStar--;
    }

    // Send an update
    SendStarUpdate(waveColor);

    // Advance the cycle index.
    m_CycleIndex = (m_CycleIndex + 1) % m_CycleSize;

    return m_Delay;
}

void SpiralTreeStars::SendStarUpdate(uint8_t color)
{
    memset(payloadData, 0, MAX_COMMAND_BUFFER);
    payloadSize = sizeof(ProgramCommand) + 5;
    ProgramCommand *pProgram = (ProgramCommand *)payloadData;
    byte* extra_data = (byte *)(payloadData + sizeof(ProgramCommand));
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.layout = STRING_LAYOUT_LINEAR;
    pProgram->command.option = COMMAND_OPTION_UPDATE | COMMAND_OPTION_GROUP_B;
    pProgram->command.address = m_Address & ~0xC000; // All tree but trunk and top

    pProgram->program = COLOR_NODE_PROGRAM_SHOOTING_STARS;

    pProgram->option = 2 << 4;
    pProgram->option |= PROGRAM_OPTION_FIXED | PROGRAM_OPTION_WAIT;
    if (m_WhiteTip)
    {
        pProgram->option |= OPTION_BIT_2;
    }
    pProgram->delay = 0;

    pProgram->pattern = color << 4;
    pProgram->pattern |= m_StarSize;

    extra_data[TICK_GAP_MIN] = 0;
    extra_data[TICK_GAP_MAX] = 0;
    extra_data[POSITION_GAP_MIN] = 0;
    extra_data[POSITION_GAP_MAX] = 0;
    extra_data[STARS_MAX] = 10;

    SendCommand();
}



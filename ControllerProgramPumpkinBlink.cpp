#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_CONTROLLER_PUMPKIN_BLINK
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <ControllerProgramPumpkinBlink.h>
#include <ColorNodeCommands.h>
#include <ColorNodeSendCommand.h>
#include <LightProgram.h>
#include <ColorUtils.h>
#include <ColorNodeUtils.h>
#include <G35String.h>


#define PUMPKIN_BULB_COUNT 11

#define COLOR_INDEX_WHITE 0
#define COLOR_INDEX_BLACK 1
#define COLOR_INDEX_ORANGE 9


ControllerProgramPumpkinBlink::ControllerProgramPumpkinBlink(G35& g35)
  : LightProgram(g35)
{
    DebugPrintf("ControllerProgramPumpkinBlink\n");
}

bool ControllerProgramPumpkinBlink::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    COLOR_INFO colorInfo;
    byte encodedOrange;

    colorInfo.palete = COLOR_PALETE_ALL;
    colorInfo.index = COLOR_INDEX_ORANGE;
    encodedOrange = EncodeColorInfo(&colorInfo);

    memset(payloadData, 0, MAX_COMMAND_BUFFER);
    RawCommand *rawCommand = (RawCommand *)payloadData;
    byte* bulb_data = (byte *)(payloadData + sizeof(RawCommand));
    rawCommand->command.type = COMMAND_RAW;
    rawCommand->bulb_delay = 0;
    rawCommand->intensity = G35::MAX_INTENSITY;
    payloadSize = sizeof(RawCommand) + PUMPKIN_BULB_COUNT;
    rawCommand->command.address = STRING_GROUP_ALL;
    rawCommand->command.option = COMMAND_OPTION_GROUP_A;
    rawCommand->command.layout = STRING_LAYOUT_LINEAR;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = PUMPKIN_BULB_COUNT - 1;
    memset(bulb_data, encodedOrange, PUMPKIN_BULB_COUNT);
    SendCommand();

    sleep(2000);

    return true;
}

uint32_t ControllerProgramPumpkinBlink::Do()
{
    COLOR_INFO colorInfo;
    byte encodedOrange;
    byte encodedWhite;
    byte encodedBlack;

    colorInfo.palete = COLOR_PALETE_ALL;
    colorInfo.index = COLOR_INDEX_ORANGE;
    encodedOrange = EncodeColorInfo(&colorInfo);

    colorInfo.palete = COLOR_PALETE_ALL;
    colorInfo.index = COLOR_INDEX_WHITE;
    encodedWhite = EncodeColorInfo(&colorInfo);

    colorInfo.palete = COLOR_PALETE_ALL;
    colorInfo.index = COLOR_INDEX_BLACK;
    encodedBlack = EncodeColorInfo(&colorInfo);

    memset(payloadData, 0, MAX_COMMAND_BUFFER);
    RawCommand *rawCommand = (RawCommand *)payloadData;
    byte* bulb_data = (byte *)(payloadData + sizeof(RawCommand));
    rawCommand->command.type = COMMAND_RAW;
    rawCommand->bulb_delay = 0;
    rawCommand->intensity = G35::MAX_INTENSITY;
    payloadSize = sizeof(RawCommand) + PUMPKIN_BULB_COUNT;
    rawCommand->command.address = STRING_GROUP_ALL;
    rawCommand->command.option = COMMAND_OPTION_GROUP_A;
    rawCommand->start_bulb = 0;
    rawCommand->end_bulb = PUMPKIN_BULB_COUNT - 1;

    memset(bulb_data, encodedOrange, PUMPKIN_BULB_COUNT);

    switch (rand() % 3)
    {
    case 0: // Pumpkin 1
        bulb_data[0] = encodedWhite;
        bulb_data[1] = encodedWhite;
        bulb_data[2] = encodedWhite;
        bulb_data[3] = encodedWhite;
        bulb_data[4] = encodedWhite;
        break;

    case 1: // Pumpkin 2
        bulb_data[5] = encodedWhite;
        bulb_data[6] = encodedWhite;
        bulb_data[7] = encodedWhite;
        bulb_data[8] = encodedWhite;
        bulb_data[9] = encodedWhite;
        break;

    case 2: // Pumpkin 3
        bulb_data[10] = encodedWhite;
        break;
    }

    SendCommand();

    delay(200);

    memset(bulb_data, encodedOrange, PUMPKIN_BULB_COUNT);

    SendCommand();

    delay_ = 3000 + (rand() % 5000);
    return delay_;
}


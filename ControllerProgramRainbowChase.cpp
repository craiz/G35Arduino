#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_CONTROLLER_RAINBOW_CHASE
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <ControllerProgramRainbowChase.h>
#include <ColorNodeCommands.h>
#include <ColorNodeSendCommand.h>
#include <LightProgram.h>
#include <G35String.h>



ControllerProgramRainbowChase::ControllerProgramRainbowChase(G35& g35)
  : LightProgram(g35),
    m_sequence(0)
{
    DebugPrintf("ControllerProgramRainbowChase\n");
}

bool ControllerProgramRainbowChase::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    DebugPrintf("Initializing\n");
    ProgramCommand* command = (ProgramCommand *)payloadData;
    payloadSize = sizeof(ProgramCommand);
    memset(command, 0, sizeof(ProgramCommand));
    command->command.type = COMMAND_PROGRAM;
    command->command.address = STRING_GROUP_ALL;
    command->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_A;
    command->command.layout = STRING_LAYOUT_LINEAR;
    command->delay = 400;
    command->option = PROGRAM_OPTION_FORWARD;
    command->program = COLOR_NODE_PROGRAM_RAINBOW;
    command->pattern = 4; // rainbow wave
    SendCommand();

    // Star uses rings layout
    command->command.address = STRING_ID_STAR;
    command->command.option = COMMAND_OPTION_DEFER;
    command->command.layout = STRING_LAYOUT_STAR_RINGS;
    SendCommand();

    // Snowflakes use reduced layout
    command->command.address = STRING_ID_SNOWFLAKE;
    command->command.option = COMMAND_OPTION_DEFER;
    command->command.layout = STRING_LAYOUT_SNOWFLAKE_REDUCED;
    SendCommand();

    // TODO: Fix snowflake grouping
    command->command.address = STRING_ID_SNOWFLAKE_2;
    command->command.option = COMMAND_OPTION_DEFER;
    command->command.layout = STRING_LAYOUT_SNOWFLAKE_REDUCED;
    SendCommand();

    // Tree top
    command->command.address = STRING_ID_TREE_TOP;
    command->command.option = COMMAND_OPTION_DEFER;
    command->command.layout = STRING_LAYOUT_TREE_TOP_DOWN_LEFT_TO_RIGHT;
    SendCommand();

    // Send commit command.
    DebugPrintf("Committing\n");
    Command* pCommand = (Command *)payloadData;
    memset(pCommand, 0, sizeof(Command));
    payloadSize = sizeof(Command);
    pCommand->type = COMMAND_COMMIT;
    pCommand->address = STRING_GROUP_ALL;
    pCommand->option = COMMAND_OPTION_GROUP_A;
    SendCommand();

    return true;
}

uint32_t ControllerProgramRainbowChase::Do()
{
    DebugPrintf("Updating\n");
    ProgramCommand* command = (ProgramCommand *)payloadData;
    payloadSize = sizeof(ProgramCommand);
    memset(command, 0, sizeof(ProgramCommand));
    command->command.type = COMMAND_PROGRAM;
    command->command.address = STRING_GROUP_ALL;
    command->command.option = COMMAND_OPTION_UPDATE | COMMAND_OPTION_GROUP_A;
    command->program = COLOR_NODE_PROGRAM_RAINBOW;
    command->pattern = 4; // rainbow wave

    switch (m_sequence )
    {
    case 0:
        command->delay = 400;
        command->option = PROGRAM_OPTION_FORWARD;
        delay_ = 1000;
        break;
    case 1:
        command->delay = 350;
        command->option = PROGRAM_OPTION_FORWARD;
        break;
    case 2:
        command->delay = 300;
        command->option = PROGRAM_OPTION_FORWARD;
        break;
    case 3:
        command->delay = 250;
        command->option = PROGRAM_OPTION_FORWARD;
        break;
    case 4:
        command->delay = 200;
        command->option = PROGRAM_OPTION_FORWARD;
        delay_ = 2000;
        break;
    case 5:
        command->delay = 150;
        command->option = PROGRAM_OPTION_FORWARD;
        break;
    case 6:
        command->delay = 100;
        command->option = PROGRAM_OPTION_FORWARD;
        break;
    case 7:
        command->delay = 50;
        command->option = PROGRAM_OPTION_FORWARD;
        break;
    case 8:
        command->delay = 20;
        command->option = PROGRAM_OPTION_FORWARD;
        delay_ = 5000;       
        break;
    case 9:
        command->delay = 50;
        command->option = PROGRAM_OPTION_FORWARD;
        delay_ = 2000;
        break;
    case 10:
        command->delay = 100;
        command->option = PROGRAM_OPTION_FORWARD;
        break;
    case 11:
        command->delay = 150;
        command->option = PROGRAM_OPTION_FORWARD;
        break;
    case 12:
        command->delay = 200;
        command->option = PROGRAM_OPTION_FORWARD;
        break;
    case 13:
        command->delay = 250;
        command->option = PROGRAM_OPTION_FORWARD;
        delay_ = 1000;
        break;
    case 14:
        command->delay = 300;
        command->option = PROGRAM_OPTION_FORWARD;
        break;
    case 15:
        command->delay = 350;
        command->option = PROGRAM_OPTION_FORWARD;
        break;
    case 16:
        command->delay = 400;
        command->option = PROGRAM_OPTION_FORWARD;
        break;

    // Change direction
    case 17:
        command->delay = 400;
        command->option = PROGRAM_OPTION_BACKWARD;
        break;
    case 18:
        command->delay = 350;
        command->option = PROGRAM_OPTION_BACKWARD;
        break;
    case 19:
        command->delay = 300;
        command->option = PROGRAM_OPTION_BACKWARD;
        break;
    case 20:
        command->delay = 250;
        command->option = PROGRAM_OPTION_BACKWARD;
        break;
    case 21:
        command->delay = 200;
        command->option = PROGRAM_OPTION_BACKWARD;
        delay_ = 2000;
        break;
    case 22:
        command->delay = 150;
        command->option = PROGRAM_OPTION_BACKWARD;
        break;
    case 23:
        command->delay = 100;
        command->option = PROGRAM_OPTION_BACKWARD;
        break;
    case 24:
        command->delay = 50;
        command->option = PROGRAM_OPTION_BACKWARD;
        break;
    case 25:
        command->delay = 20;
        command->option = PROGRAM_OPTION_BACKWARD;
        delay_ = 5000;
        break;
    case 26:
        command->delay = 50;
        command->option = PROGRAM_OPTION_BACKWARD;
        delay_ = 2000;
        break;
    case 27:
        command->delay = 100;
        command->option = PROGRAM_OPTION_BACKWARD;
        break;
    case 28:
        command->delay = 150;
        command->option = PROGRAM_OPTION_BACKWARD;
        break;
    case 29:
        command->delay = 200;
        command->option = PROGRAM_OPTION_BACKWARD;
        break;
    case 30:
        command->delay = 250;
        command->option = PROGRAM_OPTION_BACKWARD;
        delay_ = 1000;
        break;
    case 31:
        command->delay = 300;
        command->option = PROGRAM_OPTION_BACKWARD;
        break;
    case 32:
        command->delay = 350;
        command->option = PROGRAM_OPTION_BACKWARD;
        break;
    case 33:
        command->delay = 400;
        command->option = PROGRAM_OPTION_BACKWARD;
        break;

    default:
        command->delay = 60000;
        command->option = PROGRAM_OPTION_FORWARD;
        delay_ = 0x8FFFFFFF;
        break;
    }

    DebugPrintf("RainbowChase: Sequence %u, Node Delay=%u, Controller Delay=%u\n", m_sequence, command->delay, delay_);

    SendCommand();

    m_sequence++;
    return delay_;
}


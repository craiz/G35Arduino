#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_CONTROLLER_ALTERNATE_DIRECTION
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <ControllerProgramAlternateDirection.h>
#include <ColorNodeCommands.h>
#include <ColorNodeUtils.h>
#include <ColorNodeSendCommand.h>
#include <LightProgram.h>
#include <G35String.h>


byte mainLayouts[] = {
        STRING_LAYOUT_LINEAR,
        STRING_LAYOUT_SIDES,
        STRING_LAYOUT_HORIZONTAL_LINES,
        STRING_LAYOUT_HORIZONTAL_LINES_CENTER,
        STRING_LAYOUT_VERTICAL_LINES,
        STRING_LAYOUT_VERTICAL_LINES_CENTER,
        STRING_LAYOUT_RINGS_CENTER,
        STRING_LAYOUT_RINGS_CORNER
        };
byte currentMainLayout = 0;


byte starLayouts[] = {
        STRING_LAYOUT_STAR_BLADES,
        STRING_LAYOUT_STAR_LINES,
        STRING_LAYOUT_STAR_RINGS,
        STRING_LAYOUT_STAR_EDGES,
        STRING_LAYOUT_STAR_WINGS
        };
byte currentStarLayout = 0;


byte snowflakeLayouts[] = {
        STRING_LAYOUT_LINEAR,
        STRING_LAYOUT_SIDES,
        STRING_LAYOUT_HORIZONTAL_LINES,
        STRING_LAYOUT_HORIZONTAL_LINES_CENTER,
        STRING_LAYOUT_RINGS_CENTER
        };
byte currentSnowflakeLayout = 0;


ControllerProgramAlternateDirection::ControllerProgramAlternateDirection(G35& g35)
  : LightProgram(g35)
{
    DebugPrintf("ControllerProgramAlternateDirection\n");
}

bool ControllerProgramAlternateDirection::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    DebugPrintf("Initializing strings...\n");

    // pick next layouts;
    currentMainLayout = (currentMainLayout + 1) % ARRAYSIZE(mainLayouts);
    currentStarLayout = (currentStarLayout + 1) % ARRAYSIZE(starLayouts);
    currentSnowflakeLayout = (currentSnowflakeLayout + 1) % ARRAYSIZE(snowflakeLayouts);

    uint16_t seed = rand();
    ProgramCommand* pProgram = (ProgramCommand *)payloadData;
    payloadSize = sizeof(ProgramCommand);

    // Roof, Tree, Yard, Bushes:
    // Always linear layout
    memset(pProgram, 0, sizeof(ProgramCommand));
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.address = STRING_GROUP_A_ROOF | STRING_GROUP_A_TREE | STRING_GROUP_A_YARD | STRING_GROUP_A_BUSHES;
    pProgram->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_A;
    pProgram->command.layout = STRING_LAYOUT_LINEAR;
    pProgram->command.seed = seed;
    pProgram->delay = DELAY_DEFAULT;
    pProgram->option = PROGRAM_OPTION_WAIT;
    pProgram->program = COLOR_NODE_PROGRAM_ALTERNATE_DIRECTION_WAVE;
    SendCommand();

    // Windows, Door:
    memset(pProgram, 0, sizeof(ProgramCommand));
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.address = STRING_GROUP_A_WINDOW | STRING_GROUP_A_DOOR;
    pProgram->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_A;
    pProgram->command.layout = mainLayouts[currentMainLayout];
    pProgram->command.seed = seed;
    pProgram->delay = DELAY_DEFAULT;
    pProgram->option = PROGRAM_OPTION_WAIT;
    pProgram->program = COLOR_NODE_PROGRAM_ALTERNATE_DIRECTION_WAVE;
    SendCommand();

    // Tree Top;
    memset(pProgram, 0, sizeof(ProgramCommand));
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.address = STRING_ID_TREE_TOP;
    pProgram->command.option = COMMAND_OPTION_DEFER;
    pProgram->command.layout = mainLayouts[currentMainLayout];
    pProgram->command.seed = seed;
    pProgram->delay = DELAY_DEFAULT;
    pProgram->option = PROGRAM_OPTION_WAIT;
    pProgram->program = COLOR_NODE_PROGRAM_ALTERNATE_DIRECTION_WAVE;
    SendCommand();

    // Star:
    memset(pProgram, 0, sizeof(ProgramCommand));
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.address = STRING_ID_STAR;
    pProgram->command.option = COMMAND_OPTION_DEFER;
    pProgram->command.layout = starLayouts[currentStarLayout];
    pProgram->command.seed = seed;
    pProgram->delay = DELAY_DEFAULT;
    pProgram->option = PROGRAM_OPTION_WAIT;
    pProgram->program = COLOR_NODE_PROGRAM_ALTERNATE_DIRECTION_WAVE;
    SendCommand();

    // Snowflake:
    memset(pProgram, 0, sizeof(ProgramCommand));
    pProgram->command.type = COMMAND_PROGRAM;
    pProgram->command.address = STRING_GROUP_ALL;
    pProgram->command.option = COMMAND_OPTION_DEFER | COMMAND_OPTION_GROUP_C;
    pProgram->command.layout = snowflakeLayouts[currentSnowflakeLayout];
    pProgram->command.seed = seed;
    pProgram->delay = DELAY_DEFAULT;
    pProgram->option = PROGRAM_OPTION_WAIT;
    pProgram->program = COLOR_NODE_PROGRAM_ALTERNATE_DIRECTION_WAVE;
    SendCommand();

    // Send commit command to apply all the commands.
    DebugPrintf("Committing\n");
    Command* pCommand = (Command *)payloadData;
    memset(pCommand, 0, sizeof(Command));
    payloadSize = sizeof(Command);
    pCommand->type = COMMAND_COMMIT;
    pCommand->address = STRING_GROUP_ALL;
    pCommand->option = COMMAND_OPTION_GROUP_A;
    SendCommand();

    delay_ = 3000;

    return true;
}

uint32_t ControllerProgramAlternateDirection::Do()
{
    DebugPrintf("Sending Update...\n");
    Command* command = (Command *)payloadData;

    command->type = COMMAND_KICK;
    command->address = STRING_GROUP_ALL;
    command->option = COMMAND_OPTION_GROUP_A;
    command->seed = rand();

    SendCommand();
  
    return delay_;
}


//*********************************************************************
//* ColorNode Controller Software 
//* by Paul Martis
//* http://www.digitalmisery.com
//* December 26, 2011
//*********************************************************************

#include <Debug.h>
#include <DebugConfig.h>
#if DEBUG_CONTROLLER
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <Ports.h>
#include <RF12.h>
#include <util/crc16.h>
#include <util/parity.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <G35.h>
#include <ColorNodeCommands.h>
#include <ColorNodeUtils.h>
#include <ColorNodeSendCommand.h>
#include <ColorNodeConfig.h>
#include <SerialPrintf.h>


//*********************************************************************
// Needed so the controller can run programs
#include <G35String.h>
#include <ProgramRunner.h>
#include <LightProgram.h>
#include <ControllerProgramSolidRainbow.h>
#include <ControllerProgramHolly.h>
#include <ControllerProgramIce.h>
#include <ControllerProgramCandyCane.h>
#include <ControllerProgramStrobe.h>
#include <ControllerProgramMeteorite.h>
#include <ControllerProgramTwinkle.h>
#include <ControllerProgramChase.h>
#include <ControllerProgramStrobe.h>
#include <ControllerProgramRainbowStrobe.h>
#include <ControllerProgramRainbowChase.h>
#include <ControllerProgramFadeInFadeOut.h>
#include <ControllerProgramAlternateDirection.h>
#include <ControllerProgramSteppedWave.h>
#include <ControllerProgramSpiralStars.h>
#include <ControllerProgramStrobeFill.h>
#include <ControllerProgramPumpkinBlink.h>
#include <ControllerProgramSeahawks.h>
#include <ControllerProgramUW.h>
#include <ControllerProgramDissolve.h>
#include <ControllerProgramCrossOverWave.h>

#include <MEORandomStrobe.h>
#include <SequenceUtils.h>

#if CURRENT_CONTROLLER_CONFIGURATION == CHRISTMAS
// Christmas Program Sequence

#define INSERT_SPORTS_COLORS 0
#define SPORTS_PROGRAM CONTROLLER_PROGRAM_SEAHAWKS

#if INSERT_SPORTS_COLORS
uint8_t program_sequence[] =
    {
        SPORTS_PROGRAM,
        CONTROLLER_PROGRAM_HOLLY,
        SPORTS_PROGRAM,
        CONTROLLER_PROGRAM_STROBE_BLUE,
        SPORTS_PROGRAM,
        CONTROLLER_PROGRAM_STEPPED_WAVE,
        SPORTS_PROGRAM,
        CONTROLLER_PROGRAM_METEORITE,
        SPORTS_PROGRAM,
        CONTROLLER_PROGRAM_ICE,
        SPORTS_PROGRAM,
        CONTROLLER_PROGRAM_STROBE_RED,
        SPORTS_PROGRAM,
        CONTROLLER_PROGRAM_RAINBOW_CHASE,
        SPORTS_PROGRAM,
        CONTROLLER_PROGRAM_CROSSOVERWAVE,
        SPORTS_PROGRAM,
        CONTROLLER_PROGRAM_CANDY_CANE,
        SPORTS_PROGRAM,
        CONTROLLER_PROGRAM_STROBE_GREEN,
        SPORTS_PROGRAM,
        CONTROLLER_PROGRAM_FADE_IN_FADE_OUT,
        SPORTS_PROGRAM,
        CONTROLLER_PROGRAM_STROBE_RAINBOW,
        SPORTS_PROGRAM,
        CONTROLLER_PROGRAM_ALTERNATE_DIRECTION,
        SPORTS_PROGRAM,
        CONTROLLER_PROGRAM_CHASE_RED_GREEN,
        SPORTS_PROGRAM,
        CONTROLLER_PROGRAM_DISSOLVE,
    };
#else
uint8_t program_sequence[] = 
    {
        CONTROLLER_PROGRAM_HOLLY,
        CONTROLLER_PROGRAM_STROBE_BLUE,
        CONTROLLER_PROGRAM_UW,
        CONTROLLER_PROGRAM_STEPPED_WAVE,
        CONTROLLER_PROGRAM_METEORITE,
        CONTROLLER_PROGRAM_ICE,
        CONTROLLER_PROGRAM_STROBE_RED,
        CONTROLLER_PROGRAM_RAINBOW_CHASE,
        CONTROLLER_PROGRAM_CROSSOVERWAVE,
        CONTROLLER_PROGRAM_CANDY_CANE,
        CONTROLLER_PROGRAM_STROBE_GREEN,
        CONTROLLER_PROGRAM_FADE_IN_FADE_OUT,
        CONTROLLER_PROGRAM_STROBE_RAINBOW,
        CONTROLLER_PROGRAM_SEAHAWKS,
        CONTROLLER_PROGRAM_ALTERNATE_DIRECTION,
        CONTROLLER_PROGRAM_CHASE_RED_GREEN,
        CONTROLLER_PROGRAM_DISSOLVE,
    };
#endif

#else
// Hallow Program Sequence
const uint8_t program_sequence[] = 
    {   CONTROLLER_PROGRAM_PUMPKIN_BLINK,
        CONTROLLER_PROGRAM_FADE_IN_FADE_OUT,
        CONTROLLER_PROGRAM_STROBE_RED,
    };
#endif
const uint8_t program_sequence_size = ARRAYSIZE(program_sequence);


uint8_t currentProgramIndex = 0;
uint32_t currentProgramDuration = 0;

G35String lights;

LightProgram* CreateProgram(uint8_t programIndex)
{
    switch (programIndex)
    {
    case CONTROLLER_PROGRAM_NULL:
        currentProgramDuration = 0x8FFFFFFF;
        return new LightProgram(lights);
    default:
    case CONTROLLER_PROGRAM_HOLLY:
        currentProgramDuration = 45000;
        return new ControllerProgramHolly(lights);
    case CONTROLLER_PROGRAM_STROBE_BLUE:
        currentProgramDuration = 30000;
        return new ControllerProgramStrobe(lights, RANDOM_STROBE_PATTERN_BLUE_WHITE);
    case CONTROLLER_PROGRAM_STEPPED_WAVE:
        currentProgramDuration = 30000;
        return new ControllerProgramSteppedWave(lights);
    case CONTROLLER_PROGRAM_METEORITE:
        currentProgramDuration = 45000;
        return new ControllerProgramMeteorite(lights);
    case CONTROLLER_PROGRAM_ICE:
        currentProgramDuration = 70000;
        return new ControllerProgramIce(lights);
    case CONTROLLER_PROGRAM_STROBE_RED:
        currentProgramDuration = 30000;
        return new ControllerProgramStrobe(lights, RANDOM_STROBE_PATTERN_RED_WHITE);
    case CONTROLLER_PROGRAM_RAINBOW_CHASE:
        currentProgramDuration = 60000;
        return new ControllerProgramRainbowChase(lights);
    case CONTROLLER_PROGRAM_CANDY_CANE:
        currentProgramDuration = 70000;
        return new ControllerProgramCandyCane(lights);
    case CONTROLLER_PROGRAM_STROBE_GREEN:
        currentProgramDuration = 30000;
        return new ControllerProgramStrobe(lights, RANDOM_STROBE_PATTERN_GREEN_WHITE);
    case CONTROLLER_PROGRAM_FADE_IN_FADE_OUT:
        currentProgramDuration = 30000;
        return new ControllerProgramFadeInFadeOut(lights);
    case CONTROLLER_PROGRAM_STROBE_RAINBOW:
        currentProgramDuration = 50000;
        return new ControllerProgramRainbowStrobe(lights);
    case CONTROLLER_PROGRAM_ALTERNATE_DIRECTION:
        currentProgramDuration = 45000;
        return new ControllerProgramAlternateDirection(lights);
    case CONTROLLER_PROGRAM_CHASE_RED_GREEN:
        currentProgramDuration = 40000;
        return new ControllerProgramChase(lights, SEQUENCE_PATTERN_RED_GREEN);
    case CONTROLLER_PROGRAM_SOLID_RAINBOW:
        currentProgramDuration = 45000;
        return new ControllerProgramSolidRainbow(lights);
    case CONTROLLER_PROGRAM_PUMPKIN_BLINK:
        currentProgramDuration = 60000;
        return new ControllerProgramPumpkinBlink(lights);
    case CONTROLLER_PROGRAM_SEAHAWKS:
        currentProgramDuration = 45000;
        return new ControllerProgramSeahawks(lights);
    case CONTROLLER_PROGRAM_UW:
        currentProgramDuration = 30000;
        return new ControllerProgramUW(lights);
    case CONTROLLER_PROGRAM_DISSOLVE:
        currentProgramDuration = 60000;
        return new ControllerProgramDissolve(lights);
    case CONTROLLER_PROGRAM_CROSSOVERWAVE:
        currentProgramDuration = 45000;
        return new ControllerProgramCrossOverWave(lights);
    }
    return NULL;
}

ProgramRunner runner(CreateProgram, CONTROLLER_PROGRAM_COUNT);

void SetProgram()
{
    DebugPrintf("SetProgram: Sequence=%u, Program=%u\n", currentProgramIndex, program_sequence[currentProgramIndex]);
    runner.SwitchProgram(program_sequence[currentProgramIndex], PATTERN_DEFAULT, OPTION_DEFAULT, DELAY_DEFAULT);
}

void AdvanceProgram()
{
    // Determine if the program should be switched.
    if (millis() > runner.GetLastSwitchMillis() + currentProgramDuration)
    {
        currentProgramIndex = (currentProgramIndex + 1) % program_sequence_size;

        SetProgram();
    }
}

//*********************************************************************

bool outputReady = false;

#define NODE_NUM 30
#define FREQ RF12_433MHZ
#define GROUP_NUM 1


//*********************************************************************
//* For sending commands via serial port
static uint16_t value;
static uint16_t stack[RF12_MAXDATA];
static byte top;


static void addCh (char* msg, char c) {
    byte n = strlen(msg);
    msg[n] = c;
}
static void addInt (char* msg, word v) {
    if (v >= 10)
        addInt(msg, v / 10);
    addCh(msg, '0' + v % 10);
}

char helpText1[] PROGMEM = 
    "\n"
    "Commands" "\n"
    "  Off: 'o'" "\n"
    "    <command option>,<address> o" "\n"
    "  Program: 'p'" "\n"
    "    <program>,<program option>,<program pattern>,<program delay>,<command option>,<command seed>,<layout>,<address> p" "\n"
    "  Wave: 'w'" "\n"
    "    <hold n>,...,<hold 0>,<color n>,...,<color 0>,<span size>,<pixel distribution>,<pixel count>,<program>,<program option>,<program pattern>,<program delay>,<command option>,<command seed>,<layout>,<address> w" "\n"
    "  Raw: 'r'" "\n"
    "    <light start>,<light start+1>,...,<light end>,<start>,<end>,<intensity>,<bulb delay>,<command option>,<command seed>,<layout>,<address> r" "\n"
    "  Kick: 'k'" "\n"
    "    <command option>,<address> k" "\n"
    "  Commit: 'c'" "\n"
    "    <command option>,<address> c" "\n"
    "  Address Config: 'a'" "\n"
    "    <new rf node>,<new rf controller>,<new rf group>,<new string group D>,<new string group C>,<new string group B>,<new string group A>,<new string id>,<string id> a" "\n"
    "  Light String Config: 'l'" "\n"
    "    <physical>,<logical>,<direction>,<delay>,<string id> l" "\n"
    "  Run Light Show: 's'" "\n"
    "     <program> s" "\n"
    "\n"
;

static void showString (PGM_P s) {
    for (;;) {
        char c = pgm_read_byte(s++);
        if (c == 0)
            break;
        if (c == '\n')
            Serial.print('\r');
        Serial.print(c);
    }
}

static void showHelp ()
{
    showString(helpText1);
}

#define PUSH(__value)   (stack[top++] = __value)
#define POP()           (stack[--top])
#define PEEK(__index)   (stack[__index])

static void handleInput (char c)
{
    bool invalidParameters = false;

    if ('0' <= c && c <= '9')
    {
        value = 10 * value + c - '0';
    }
    else if (c == ',')
    {
        if (top < sizeof stack)
        {
            stack[top++] = value;
        }
        value = 0;
    } 
    else if ('a' <= c && c <='z')
    {
        stack[top++] = value;
        
        // Optimistically assume we will have a valid command to send.
        outputReady = true;
        memset(payloadData, 0, sizeof(payloadData));
        payloadSize = 0;
        
        switch (c) 
        {
            default:
            {
                invalidParameters = true;
                break;
            }
            case 'p':   // Program Command
            {
                DebugPrintf("Parsing Program Command\n");
                if (top != 8)
                {
                    invalidParameters = true;
                    break;
                }

                //     8            7                6                  5              4                3           2        1
                // <program>,<program option>,<program pattern>,<program delay>,<command option>,<command seed>,<layout>,<address> p
                ProgramCommand *program = (ProgramCommand *)payloadData;
                program->command.type= COMMAND_PROGRAM;
                program->command.address = stack[top - 1];
                program->command.layout = stack[top - 2];
                program->command.seed = stack[top - 3];
                program->command.option = stack[top - 4];
                program->delay = stack[top - 5];
                program->pattern = stack[top - 6];
                program->option = stack[top - 7];
                program->program = stack[top - 8];
                payloadSize = sizeof(ProgramCommand);
                break;
            }
            case 'w':   // Wave Program Command
            {
                DebugPrintf("Parsing Wave Program Command\n");
                if (top < 12)
                {
                    invalidParameters = true;
                    break;
                }

                //                                     12        11              10                 9           8            7                6                 5               4               3            2        1
                // <hold n>...<hold 0>,<color n>...<color 0>,<span size>,<pixel distribution>,<pixel count>,<program>,<program option>,<program pattern>,<program delay>,<command option>,<command seed>,<layout>,<address> w
                ProgramCommand *program = (ProgramCommand *)payloadData;
                program->command.type= COMMAND_PROGRAM;
                program->command.address = stack[top - 1];
                program->command.layout = stack[top - 2];
                program->command.seed = stack[top - 3];
                program->command.option = stack[top - 4];
                program->delay = stack[top - 5];
                program->pattern = stack[top - 6];
                program->option = stack[top - 7];
                program->program = stack[top - 8];

                byte * extraData = payloadData + sizeof(ProgramCommand);
                extraData[0] = stack[top - 9]; // pixel count
                extraData[1] = stack[top - 10]; // pixel distribution
                extraData[2] = stack[top - 11]; // span size
                byte * colors = &extraData[3];
                byte * holds = colors + program->pattern;
                byte stackOffset = 12;
                for (byte i = 0; i < program->pattern; i++)
                {
                    colors[i] = stack[top - stackOffset++];
                }
                for (byte i = 0; i < program->pattern; i++)
                {
                    holds[i] = stack[top - stackOffset++];
                }
                
                payloadSize = sizeof(ProgramCommand) + (program->pattern * 2) + 3;
                break;
            }            

            case 'r':   // raw command
            {
                DebugPrintf("Parsing Raw Command\n");
                if (top < 10)
                {
                    invalidParameters = true;
                    break;
                }

                //                                                 8      7       6            5               4              3            2        1
                //<light start>,<light start+1>,...,<light end>,<start>,<end>,<intensity>,<bulb delay>,<command option>,<command seed>,<layout>,<address> r
                RawCommand *raw = (RawCommand *)payloadData;
                raw->command.type = COMMAND_RAW;
                raw->command.address = stack[top - 1];
                raw->command.layout = stack[top - 2];
                raw->command.seed = stack[top - 3];
                raw->command.option = stack[top - 4];
                raw->bulb_delay = stack[top - 5];
                raw->intensity = stack[top - 6];
                raw->end_bulb = stack[top - 7];
                raw->start_bulb = stack[top - 8];

                uint8_t lightCount = ((raw->end_bulb - raw->start_bulb) + 1);
                if (lightCount <= MAX_LIGHTS)
                {
                    byte *colorArray = payloadData + sizeof(RawCommand);
                    uint8_t stackOffset = lightCount - 1;
                    for (uint8_t i = 0; i < lightCount; i++)
                    {
                        DebugPrintf("Bulb: %u Color: %u\n", i, stack[top - (9 + stackOffset)]);
                        colorArray[i] = stack[top - (9 + stackOffset)];
                        stackOffset--;
                    }
                    payloadSize = sizeof(RawCommand) + lightCount;
                }
                else
                {
                    DebugPrintf("Invalid light count: %u\n", lightCount);
                    outputReady = false;
                }
                break;
            }
            case 'k': // kick command
            {
                DebugPrintf("Parsing Kick Command\n");
                if (top != 2)
                {
                    invalidParameters = true;
                    break;
                }

                //         2            1
                // <command option>,<address> o
                Command *command = (Command *)payloadData;
                command->type = COMMAND_KICK;
                command->address = stack[top - 1];
                command->option = stack[top - 2];

                payloadSize = sizeof(Command);
                break;
            }
            case 'o': // off command
            {
                DebugPrintf("Parsing Off Command\n");
                if (top != 2)
                {
                    invalidParameters = true;
                    break;
                }

                //         2            1
                // <command option>,<address> o
                Command *command = (Command *)payloadData;
                command->type = COMMAND_OFF;
                command->address = stack[top - 1];
                command->option = stack[top - 2];

                payloadSize = sizeof(Command);
                break;
            }
            case 'c':   // commit command
            {
                DebugPrintf("Parsing Commit Command\n");
                if (top != 2)
                {
                    invalidParameters = true;
                    break;
                }

                //         2            1
                // <command option>,<address> c
                Command *command = (Command *)payloadData;
                command->type = COMMAND_COMMIT;
                command->address = stack[top - 1];
                command->option = stack[top - 2];

                payloadSize = sizeof(Command);
                break;
            }
            case 'a':   // address config command
            {
                DebugPrintf("Parsing Address Config Command\n");
                if (top != 9)
                {
                    invalidParameters = true;
                    break;
                }

                //       9               8                7                 6                    5                    4                    3                    2            1
                // <new rf node>,<new rf controller>,<new rf group>,<new string group D>,<new string group C>,<new string group B>,<new string group A>,<new string id>,<string id> a
                // Note: Always uses string id addressing.
                ConfigAddressCommand *config = (ConfigAddressCommand *)payloadData;
                config->command.type = COMMAND_ADDRESS_CONFIG;
                config->command.address = stack[top - 1];
                config->string_id = stack[top - 2];
                config->string_groups[0] = stack[top - 3];
                config->string_groups[1] = stack[top - 4];
                config->string_groups[2] = stack[top - 5];
                config->string_groups[3] = stack[top - 6];
                config->rf_group = stack[top - 7];
                config->rf_controller = stack[top - 8];
                config->rf_node = stack[top - 9];

                payloadSize = sizeof(ConfigAddressCommand);
                break;
            }
            case 'l':   // light string config command
            {
                DebugPrintf("Parsing Light String Config Command\n");
                if (top != 5)
                {
                    invalidParameters = true;
                    break;
                }

                //     5          4         3          2        1
                // <physical>,<logical>,<direction>,<delay>,<string id> l
                // Note: Always uses string id addressing.
                ConfigLightStringCommand *config = (ConfigLightStringCommand *)payloadData;
                config->command.type = COMMAND_LIGHTSTRING_CONFIG;
                config->command.address = stack[top - 1];
                config->enumerationDelay = stack[top - 2];
                config->enumerationDirection = stack[top - 3];
                config->logicalCount = stack[top - 4];
                config->physicalCount = stack[top - 5];
            
                payloadSize = sizeof(ConfigLightStringCommand);
                break;
            }

            case 's':   // run light show
            {
                DebugPrintf("Parsing Run Light Show Command\n");
                if ((top != 1) || (stack[top - 1] >= CONTROLLER_PROGRAM_COUNT))
                {
                    invalidParameters = true;
                    break;
                }

                //     1
                // <program> s
                runner.SwitchProgram(stack[top - 1], 0, 0, 0);
                outputReady = false;
            }
        }
        value = top = 0;
        memset(stack, 0, sizeof stack);
    } 
    else if (c > ' ')
    {
        invalidParameters = true;
    }

    if (invalidParameters)
    {
        DebugPrintf("Invalid parameters!\n");
        outputReady = false;
        showHelp();
    }
}


//*********************************************************************
//* Setup Function
void setup()
{
    Serial.begin(57600);

#if DEBUG_CONFIG
    ShowNodeConfiguration(COLOR_NODE_CONTROLLER, NODE_NUM, GROUP_NUM, 0, FREQ);
#endif

    rf12_encrypt(0);
    rf12_initialize(NODE_NUM, FREQ, GROUP_NUM);
    rf12_control(0xC647);
    rf12_easyInit(0);

#if DEBUG_ENABLED
    if (MAX_COMMAND_BUFFER > RF12_MAXDATA)
    {
        DebugPrintf("Invalid configuration: MAX_COMMAND_BUFFER > RF12_MAXDATA\n");
        while (1)
        {
        }
    }
#endif

    // Seed random number generator.
    srand(analogRead(0));

    // Setup the program runner.
    DebugPrintf("Sequence Size=%u\n", program_sequence_size);
    DebugPrintf("Program Count=%u\n", CONTROLLER_PROGRAM_COUNT);
    runner.SetAutoAdvanceEnabled(false);
    SetProgram();
}

//*********************************************************************
//* Main Loop
void loop()
{
    if (Serial.available())
    {
        // Switch to NULL program before processing input.  This will stop any previously running program.
        currentProgramIndex = 0;
        runner.SwitchProgram(0, PATTERN_DEFAULT, OPTION_DEFAULT, DELAY_DEFAULT);
        handleInput(Serial.read());
    }
    
    if (outputReady)
    {
        outputReady = false;
        SendCommand();
    }

    AdvanceProgram();

    runner.loop();
}
//*********************************************************************

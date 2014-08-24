//*********************************************************************
//* ColorNode Node Software 
//* by Paul Martis
//* http://www.digitalmisery.com
//* December 4, 2011
//*********************************************************************

#include <Debug.h>
#include <DebugConfig.h>
#if DEBUG_NODE
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <EEPROM.h>
#include <Ports.h>
#include <RF12.h>
#include <G35String.h>
#include <ColorNodeCommands.h>
#include <ColorNodeSendCommand.h>
#include <ColorNodeConfig.h>
#include <ColorNodeUtils.h>
#include <LightProgram.h>
#include <ProgramRunner.h>
#include <StockPrograms.h>

#include <SerialPrintf.h>

#include <Meteorite.h>
#include <Twinkle.h>
#include <RedGreenChase.h>
#include <Pulse.h>
#include <Orbit.h>
#include <Cylon.h>
#include <Stereo.h>
#include <Inchworm.h>
#include <Rainbow.h>
#include <Creepers.h>
#include <SpookyFlicker.h>
#include <Eyes.h>
#include <PumpkinChase.h>
#include <SpookySlow.h>
#include <RandomFade.h>
#include <MEOSwitchOff.h>
#include <MEOWhites.h>
#include <MEORandomStrobe.h>
#include <MEOSimplexNoise.h>
#include <MEOSineWave.h>
#include <MEOChasing.h>
#include <MEOColorPhasing.h>
#include <MEODither.h>
#include <MEOOscillate.h>
#include <Chase.h>
#include <RawProgram.h>
#include <Solid.h>
#include <Wave.h>
#include <StrobeFill.h>
#include <ShootingStars.h>
#include <Dissolve.h>
#include <DripFill.h>
#include <Test.h>

void(* resetFunc) (void) = 0; //declare reset function @ address 0

//*********************************************************************

#define OUT_PIN 19  //Arduino pin #

#define PHYSICAL_LIGHT_COUNT_DEFAULT    50
#define LOGICAL_LIGHT_COUNT_DEFAULT     50
#define ENUMERATION_DIRECTION_DEFAULT    1  // forward
#define ENUMERATION_DELAY_DEFAULT       50

#define RF_NODE_ID_DEFAULT               1  // This node id (1-30)
#define RF_CONTROLLER_ID_DEFAULT        30  // Node ID of the controller
#define RF_GROUP_ID_DEFAULT              1  // RF group id
#define STRING_ID_DEFAULT                1  // This string id (0-255)
#define STRING_GROUP_DEFAULT             0  // No group association


#define RF_ID_MIN                1
#define RF_ID_MAX               30

#define STRING_ID_MIN             0
#define STRING_ID_MAX           255

#define STRING_GROUP_MIN         1
#define STRING_GROUP_MAX        15

#define INVALID_CONFIG_VALUE    0

#define FREQ RF12_433MHZ


//*********************************************************************
// Define how the string is configured.  This allows for different layouts.

#define STRING_TYPE_LINEAR          0
#define STRING_TYPE_STAR            1
#define STRING_TYPE_SNOWFLAKE       2
#define STRING_TYPE_WINDOW_SMALL    3
#define STRING_TYPE_WINDOW_BIG      4
#define STRING_TYPE_GARAGE_SMALL    5
#define STRING_TYPE_GARAGE_BIG      6
#define STRING_TYPE_FRONT_DOOR      7
#define STRING_TYPE_TREE_TOP        8


// Change this to define the string configuration.
#define STRING_TYPE     STRING_TYPE_LINEAR

#if (STRING_TYPE == STRING_TYPE_LINEAR)

G35String lights;

#elif (STRING_TYPE == STRING_TYPE_STAR)

#include <G35StringStar.h>
G35StringStar lights;

#elif (STRING_TYPE == STRING_TYPE_SNOWFLAKE)

#include <G35StringSnowFlake.h>
G35StringSnowflake lights;

#elif (STRING_TYPE == STRING_TYPE_WINDOW_SMALL)

#include <G35StringWindowSmall.h>
G35StringWindowSmall lights;

#elif (STRING_TYPE == STRING_TYPE_WINDOW_BIG)

#include <G35StringWindowBig.h>
G35StringWindowBig lights;

#elif (STRING_TYPE == STRING_TYPE_GARAGE_SMALL)

#include <G35StringGarageSmall.h>
G35StringGarageSmall lights;

#elif (STRING_TYPE == STRING_TYPE_GARAGE_BIG)

#include <G35StringGarageBig.h>
G35StringGarageBig lights;

#elif (STRING_TYPE == STRING_TYPE_FRONT_DOOR)

#include <G35StringFrontDoor.h>
G35StringFrontDoor lights;

#elif (STRING_TYPE == STRING_TYPE_TREE_TOP)

#include <G35StringTreeTop.h>
G35StringTreeTop lights;

#endif

uint8_t myRFNodeID = INVALID_CONFIG_VALUE;
uint8_t myRFControllerID = INVALID_CONFIG_VALUE;
uint8_t myRFGroupID = INVALID_CONFIG_VALUE;
uint8_t myStringID = INVALID_CONFIG_VALUE;
uint8_t myStringGroups[4] = {INVALID_CONFIG_VALUE};
uint8_t myPhysicalLightCount = INVALID_CONFIG_VALUE;
uint8_t myLogicalLightCount = INVALID_CONFIG_VALUE;
uint8_t myEnumerationDirection = ENUMERATION_DIRECTION_DEFAULT;
uint16_t myEnumerationDelay = ENUMERATION_DELAY_DEFAULT;

bool commandSetup = false;
uint8_t lastCommandSequence;

// Command data
byte deferredCommandBuffer[MAX_COMMAND_BUFFER];
byte activeCommandBuffer[MAX_COMMAND_BUFFER];


//*********************************************************************
// Interface for program runner

LightProgram* CreateProgram(uint8_t programIndex)
{
    switch (programIndex)
    {
    case COLOR_NODE_PROGRAM_SWITCH_OFF:
        return new MEOSwitchOff(lights);

    case COLOR_NODE_PROGRAM_WHITES:
        return new MEOWhites(lights);

    default:
    case COLOR_NODE_PROGRAM_STEADY_MULTI:
        return new SteadyMulti(lights);

    case COLOR_NODE_PROGRAM_CROSS_OVER_WAVE:
        return new CrossOverWave(lights);

    case COLOR_NODE_PROGRAM_FORWARD_WAVE:
        return new ForwardWave(lights);

    case COLOR_NODE_PROGRAM_ALTERNATE_DIRECTION_WAVE:
        return new AlternateDirectionalWave(lights);

    case COLOR_NODE_PROGRAM_FADE_SINGLE_COLORS:
        return new FadeInFadeOutSingleColors(lights);

    case COLOR_NODE_PROGRAM_BIDIRECTIONAL_WAVE:
        return new BidirectionalWave(lights);

    case COLOR_NODE_PROGRAM_FADE_MULTI_COLORS:
        return new FadeInFadeOutMultiColors(lights);

    case COLOR_NODE_PROGRAM_METEORITE:
        return new Meteorite(lights);

    case COLOR_NODE_PROGRAM_TWINKLE:
        return new Twinkle(lights);

    case COLOR_NODE_PROGRAM_RAINBOW:
        return new Rainbow(lights);

    case COLOR_NODE_PROGRAM_RANDOM_STROBE:
        return new MEORandomStrobe(lights);

    // Paul's Programs
    case COLOR_NODE_PROGRAM_RAW:
        return new RawProgram(lights, (RawCommand *)activeCommandBuffer);

    case COLOR_NODE_PROGRAM_RANDOM_FADE:
        return new RandomFade(lights, (ProgramCommand *)activeCommandBuffer);

    case COLOR_NODE_PROGRAM_CHASE:
        return new Chase(lights, (ProgramCommand *)activeCommandBuffer);

    case COLOR_NODE_PROGRAM_SOLID:
        return new Solid(lights);

    case COLOR_NODE_PROGRAM_WAVE:
        return new Wave(lights, (ProgramCommand *)activeCommandBuffer);

    case COLOR_NODE_PROGRAM_STROBE_FILL:
        return new StrobeFill(lights, (ProgramCommand *)activeCommandBuffer);

    case COLOR_NODE_PROGRAM_SHOOTING_STARS:
        //return new ShootingStars(lights, (ProgramCommand *)activeCommandBuffer);

    case COLOR_NODE_PROGRAM_DISSOLVE:
        //return new Dissolve(lights, (ProgramCommand *)activeCommandBuffer);

    case COLOR_NODE_PROGRAM_DRIP_FILL:
        return new DripFill(lights, (ProgramCommand *)activeCommandBuffer);

    case COLOR_NODE_PROGRAM_TEST:
        return new Test(lights);

    // Halloween Programs
    //case 18: return new Eyes(lights);
    //case 19: return new Creepers(lights);
    //case 20: return new PumpkinChase(lights);
    //case 23: return new SpookySlow(lights);
    //case 24: return new SpookyFlicker(lights);

        break;
    }

    //return NULL;
}

ProgramRunner runner(CreateProgram, COLOR_NODE_PROGRAM_COUNT);

//*********************************************************************
//* Setup Function
void setup()
{
    // Start the UART
#if DEBUG_NODE_ANY
    Serial.begin(57600);
#endif
    DebugPrintf("Setup\n");

    // Load configuration parameters from EEPROM    
    myRFNodeID = EEPROM.read(EEPROM_RF_NODE_ID);
    if (myRFNodeID == INVALID_CONFIG_VALUE || myRFNodeID < RF_ID_MIN || myRFNodeID > RF_ID_MAX)
    {
        myRFNodeID = RF_NODE_ID_DEFAULT;
    }
    myRFGroupID = EEPROM.read(EEPROM_RF_GROUP_ID);
    if (myRFGroupID == INVALID_CONFIG_VALUE || myRFGroupID < RF_ID_MIN || myRFGroupID > RF_ID_MAX)
    {
        myRFGroupID = RF_GROUP_ID_DEFAULT;
    }
    myRFControllerID = EEPROM.read(EEPROM_RF_CONTROLLER_ID);
    if (myRFControllerID == INVALID_CONFIG_VALUE  || myRFControllerID < RF_ID_MIN || myRFControllerID > RF_ID_MAX)
    {
        myRFControllerID = RF_CONTROLLER_ID_DEFAULT;
    }
    myStringID = EEPROM.read(EEPROM_STRING_ID);
    if (myStringID == INVALID_CONFIG_VALUE  || myStringID < STRING_ID_MIN || myStringID > STRING_ID_MAX)
    {
        myStringID = STRING_ID_DEFAULT;
    }
    for (uint8_t i = 0; i < STRING_GROUP_COUNT; i++)
    {
        myStringGroups[i] = EEPROM.read(EEPROM_STRING_GROUPS + i);
        if (myStringGroups[i] == INVALID_CONFIG_VALUE  || myStringGroups[i] < STRING_GROUP_MIN || myStringGroups[i] > STRING_GROUP_MAX)
        {
            myStringGroups[i] = STRING_GROUP_DEFAULT;
        }
    }
    myPhysicalLightCount = EEPROM.read(EEPROM_PHYSICAL_COUNT);
    if (myPhysicalLightCount == INVALID_CONFIG_VALUE)
    {
        myPhysicalLightCount = PHYSICAL_LIGHT_COUNT_DEFAULT;
    }
    myLogicalLightCount = EEPROM.read(EEPROM_LOGICAL_COUNT);
    if (myLogicalLightCount == INVALID_CONFIG_VALUE)
    {
        myLogicalLightCount = LOGICAL_LIGHT_COUNT_DEFAULT;
    }
    myEnumerationDirection = EEPROM.read(EEPROM_ENUMERATION_DIRECTION);
    myEnumerationDelay = 0;
    for (uint8_t i = 0; i < sizeof(myEnumerationDelay); i++)
    {
        myEnumerationDelay = (myEnumerationDelay << 8) | (EEPROM.read(EEPROM_ENUMERATION_DELAY + i) & 0xFF);

    }
    if (myEnumerationDelay == INVALID_CONFIG_VALUE || myEnumerationDelay == 0xFFFF)
    {
        myEnumerationDelay = ENUMERATION_DELAY_DEFAULT;
    }

    // For when things go horribly wrong
#if 0
    myRFNodeID = RF_NODE_ID_DEFAULT;
    myRFGroupID = RF_GROUP_ID_DEFAULT;
    myRFControllerID = RF_CONTROLLER_ID_DEFAULT;
    myStringID = STRING_ID_DEFAULT;
    memset(myStringGroups, STRING_GROUP_DEFAULT, STRING_GROUP_COUNT);
    myPhysicalLightCount = PHYSICAL_LIGHT_COUNT_DEFAULT;
    myLogicalLightCount = LOGICAL_LIGHT_COUNT_DEFAULT;
    myEnumerationDirection = ENUMERATION_DIRECTION_DEFAULT;
    myEnumerationDelay = ENUMERATION_DELAY_DEFAULT;
#endif

    lights.Configure(OUT_PIN, myPhysicalLightCount, myLogicalLightCount, (bool)myEnumerationDirection, STRING_LAYOUT_DEFAULT);

#if DEBUG_CONFIG
    ShowNodeConfiguration(COLOR_NODE_NODE, myRFNodeID, myRFGroupID, myRFControllerID, FREQ);
    ShowStringConfiguration(myStringID, myStringGroups, STRING_TYPE, myPhysicalLightCount, myLogicalLightCount, myEnumerationDirection, myEnumerationDelay);
#endif

    // Seed random number generator.
    srand(analogRead(0));

    // Initialize light string
    delay(myEnumerationDelay);
    lights.enumerate();
    delay(50);

    //lights.do_test_patterns();

    // Initialize command buffers
    memset(deferredCommandBuffer, 0, sizeof(deferredCommandBuffer));
    memset(activeCommandBuffer, 0, sizeof(activeCommandBuffer));

    lastCommandSequence = 255;

    // Initialize RF
    rf12_encrypt(0);
    rf12_initialize(myRFNodeID, FREQ, myRFGroupID);
    rf12_control(0xC647); //Slows down RF data rate to 4.8kbps

    // Setup initial command for default program to run on the lights.
    ProgramCommand *pProgramCommand = (ProgramCommand *)activeCommandBuffer;
    pProgramCommand->command.type = COMMAND_PROGRAM;
    pProgramCommand->command.address = myStringID;
    pProgramCommand->command.option = COMMAND_OPTION_NONE;
    pProgramCommand->program = COLOR_NODE_PROGRAM_STEADY_MULTI;
    pProgramCommand->pattern = PATTERN_DEFAULT;
    pProgramCommand->delay = DELAY_DEFAULT;
    pProgramCommand->option = OPTION_DEFAULT;

    runner.SetAutoAdvanceEnabled(false);

#if DEBUG_ENABLED
    if (MAX_COMMAND_BUFFER > RF12_MAXDATA)
    {
        DebugPrintf("Invalid configuration: MAX_COMMAND_BUFFER > RF12_MAXDATA\n");
        while (1) {}
    }
#endif
}

ADDRESSED_AS GetAddressedAs(Command *pCommand)
{
    if (myRFControllerID != (rf12_hdr & RF12_HDR_MASK))
    {
        DebugPrintf("Command sent by unrecognized controller, ignoring\n");
        return ADDRESSED_AS_NONE;
    }
    else if (((pCommand->option & COMMAND_OPTION_GROUP_MASK) == 0) && pCommand->address == myStringID)
    {
        DebugPrintf("Command addressed to me by id.\n");
        return ADDRESSED_AS_ID;
    }
    else
    {   
        uint8_t group = 0x10;
        for (uint8_t i = 0; i < STRING_GROUP_COUNT; i++)
        {
            group = group << i;

            if ((pCommand->option & group) && IS_STRING_GROUP(pCommand->address, myStringGroups[i]))
            {
                DebugPrintf("Command addressed to me by group %c.\n", 'A' + i);
                return ADDRESSED_AS_GROUP;
            }
        }
    }

    DebugPrintf("Command not for me\n");
    return ADDRESSED_AS_NONE;
}


//*********************************************************************
//* Main Loop
void loop()
{
    Command *pActiveCommand = (Command *)activeCommandBuffer;
    ProgramCommand *pProgramCommand = (ProgramCommand *)activeCommandBuffer;
    
    if (rf12_recvDone() && (rf12_crc == 0)) 
    {
        if (rf12_len < sizeof(Command) || rf12_len > MAX_COMMAND_BUFFER)
        {
            DebugPrintf("Invalid RF buffer: min=%u max=%u actual=%u\n", sizeof(Command), MAX_COMMAND_BUFFER, rf12_len);
            return;
        }

        Command *pNewCommand = (Command *)rf12_data;

        // Useful for debugging
        DebugPrintf("\n");
        DebugPrintf("Packet Received\n");
        DebugPrintf("  HDR CTL: 0x%02x\n", rf12_hdr & RF12_HDR_CTL);
        DebugPrintf("  HDR DST: 0x%02x\n", rf12_hdr & RF12_HDR_DST);
        DebugPrintf("  HDR ACK: 0x%02x\n", rf12_hdr & RF12_HDR_ACK);
        DebugPrintf("  HDR NODE: %u\n", rf12_hdr & RF12_HDR_MASK);
        DebugPrintf("  Length: %u\n", rf12_len);
        DebugPrintf("  Command\n");
        DebugPrintf("    Address: %u - 0x%04x\n", pNewCommand->address, pNewCommand->address);
        DebugPrintf("    Sequence: %u\n", pNewCommand->sequence);
        DebugPrintf("    Type: %u\n", pNewCommand->type);
        DebugPrintf("    Layout: 0x%02x\n", pNewCommand->layout);
        DebugPrintf("    Seed: 0x%04x\n", pNewCommand->seed);
        DebugPrintf("    Option: 0x%02x\n", pNewCommand->option);

        // Handle the command if sent from my controller to my string group or string id.
        ADDRESSED_AS addressed = GetAddressedAs(pNewCommand);
        if (addressed == ADDRESSED_AS_ID || addressed == ADDRESSED_AS_GROUP)
        {
            if (pNewCommand->sequence == lastCommandSequence)
            {
                // Don't do anything if this is a duplicate command.
                DebugPrintf("Duplicate command, ignoring\n");
            }
            else if ((pNewCommand->option & COMMAND_OPTION_DEFER))
            {
                // Store the command if requested.  This allows multiple strings to be synchronized with different commands.
                // We will get a commit command in the future and the deferred command will become active.
                DebugPrintf("Storing deferred command\n");
                memcpy(deferredCommandBuffer, (void *)rf12_data, rf12_len);
            }
            else if (pNewCommand->type == COMMAND_COMMIT)
            {
                // Make the deferred buffer the active buffer
                DebugPrintf("Committing deferred command\n");
                memcpy(activeCommandBuffer, deferredCommandBuffer, MAX_COMMAND_BUFFER);
                commandSetup = false;
            }
            else if (pNewCommand->type == COMMAND_KICK)
            {
                // This command will "kick" the current program without altering any parameters.
                DebugPrintf("Kicking current program\n");
                runner.Kick();
            }
            else
            {
                // This is a new command to be handled.
                DebugPrintf("New command\n");
                memcpy(activeCommandBuffer, (void *)rf12_data, rf12_len);
                commandSetup = false;
            }

            // ACK the command if requested.
            // Payload is myStringID.
            if (pNewCommand->option & COMMAND_OPTION_ACKNOWLEDGE)
            {
                DebugPrintf("Sending Ack\n");
                rf12_sendStart(RF12_HDR_CTL | RF12_HDR_DST | (myRFControllerID & RF12_HDR_MASK), &myStringID, sizeof(myStringID));
                rf12_sendWait(0);
            }

            // Update the last sequence so we will ignore any duplicate commands sent by the controller.
            lastCommandSequence = pNewCommand->sequence;
            
            if (!commandSetup)
            {
                // Re-seed the random generator if instructed to do so..
                if (pActiveCommand->seed != RANDOM_SEED_PRESERVE)
                {
                    if (pActiveCommand->seed == RANDOM_SEED_RESET)
                    {
                        pActiveCommand->seed = (myStringID + 1) * (analogRead(0) + 1);
                    }
                    DebugPrintf("Setting random seed: %u\n", pActiveCommand->seed);
                    srand(pActiveCommand->seed);
                }

                // Update the layout
                if (pActiveCommand->layout != STRING_LAYOUT_DEFAULT)
                {
                    lights.set_layout((STRING_LAYOUT)pActiveCommand->layout);
                }
            }
        } 
    }

    // Process command
    switch (pActiveCommand->type)
    {
        default:
        {
            if (!commandSetup)
            {
                DebugPrintf("Unknown command %u\n", pActiveCommand->type);
                commandSetup = true;
            }
            break;
        }
        case COMMAND_OFF:
        {
            if (!commandSetup)
            {
                DebugPrintf("Command: Off\n");

                // Switch to the SwitchOff program.
                runner.SetAutoAdvanceEnabled(false);
                runner.SwitchProgram(COLOR_NODE_PROGRAM_SWITCH_OFF, PATTERN_DEFAULT, OPTION_DEFAULT, DELAY_DEFAULT);
                commandSetup = true;
            }

            runner.loop();
            break;
        }
        case COMMAND_RAW:
        {
            if (!commandSetup)
            {
                DebugPrintf("Command: Raw\n");
            
                // Switch to the RawProgram
                runner.SwitchProgram(COLOR_NODE_PROGRAM_RAW, PATTERN_DEFAULT, OPTION_DEFAULT, DELAY_DEFAULT);
                commandSetup = true;
            }
            runner.loop();
            break;
        }
        case COMMAND_PROGRAM:
        {
            if (!commandSetup)
            {
                // Setup a new command or update the existing one.
                DebugPrintf("Command: Program\n");
                DebugPrintf("  Program: %u\n", pProgramCommand->program);
                DebugPrintf("  Option: 0x%02x\n", pProgramCommand->option);
                DebugPrintf("  Pattern: 0x%02x\n", pProgramCommand->pattern);
                DebugPrintf("  Delay: 0x%04x\n", pProgramCommand->delay);

                if (pProgramCommand->command.option & COMMAND_OPTION_UPDATE)
                {
                    // This is an update command.  Update the existing one.
                    runner.UpdateProgram(pProgramCommand->program, pProgramCommand->pattern, pProgramCommand->option, pProgramCommand->delay);
                }
                else
                {
                    // This is a new command.  Set it up.
                    runner.SwitchProgram(pProgramCommand->program, pProgramCommand->pattern, pProgramCommand->option, pProgramCommand->delay);
                }
                commandSetup = true;
            }

            runner.loop();
            break;
        }
        case COMMAND_ADDRESS_CONFIG:
        {
            if (!commandSetup)
            {
                ConfigAddressCommand *pConfigCommand = (ConfigAddressCommand *)activeCommandBuffer;
                DebugPrintf("Command: Address Config\n");
                DebugPrintf("  RF Node: %u\n", pConfigCommand->rf_node);
                DebugPrintf("  RF Group: %u\n", pConfigCommand->rf_group);
                DebugPrintf("  RF Controller: %u\n", pConfigCommand->rf_controller);
                DebugPrintf("  String ID: %u\n", pConfigCommand->string_id);
                for (uint8_t i = 0; i < STRING_GROUP_COUNT; i++)
                {
                    DebugPrintf("  String Group %c: 0x%04x\n", 'A' + i, pConfigCommand->string_groups[i]);
                }

                EEPROM.write(EEPROM_RF_NODE_ID, pConfigCommand->rf_node);
                EEPROM.write(EEPROM_RF_GROUP_ID, pConfigCommand->rf_group);
                EEPROM.write(EEPROM_RF_CONTROLLER_ID, pConfigCommand->rf_controller);
                EEPROM.write(EEPROM_STRING_ID, pConfigCommand->string_id);
                for (uint8_t i = 0; i < STRING_GROUP_COUNT; i++)
                {
                    EEPROM.write(EEPROM_STRING_GROUPS + i, pConfigCommand->string_groups[i]);
                }

                commandSetup = true;
                resetFunc();
            }
            break;
        }
        case COMMAND_LIGHTSTRING_CONFIG:
        {
            if (!commandSetup)
            {
                ConfigLightStringCommand *pConfigCommand = (ConfigLightStringCommand *)activeCommandBuffer;
                DebugPrintf("Command: Light Count Config\n");
                DebugPrintf("  Physical: %u\n", pConfigCommand->physicalCount);
                DebugPrintf("  Logical: %u\n", pConfigCommand->logicalCount);
                DebugPrintf("  Direction: %u\n", pConfigCommand->enumerationDirection);
                DebugPrintf("  Delay: %u\n", pConfigCommand->enumerationDelay);
                DebugPrintf("  Delay(Low): %u\n", lowByte(pConfigCommand->enumerationDelay));
                DebugPrintf("  Delay(High): %u\n", highByte(pConfigCommand->enumerationDelay));

                EEPROM.write(EEPROM_PHYSICAL_COUNT, pConfigCommand->physicalCount);
                EEPROM.write(EEPROM_LOGICAL_COUNT, pConfigCommand->logicalCount);
                EEPROM.write(EEPROM_ENUMERATION_DIRECTION, pConfigCommand->enumerationDirection);
                EEPROM.write(EEPROM_ENUMERATION_DELAY, highByte(pConfigCommand->enumerationDelay));
                EEPROM.write(EEPROM_ENUMERATION_DELAY + 1, lowByte(pConfigCommand->enumerationDelay));


                commandSetup = true;
                resetFunc();
            }
            break;
        }
    }
}
//*********************************************************************

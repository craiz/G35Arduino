#ifndef _COLOR_NODE_COMMANDS_H_
#define _COLOR_NODE_COMMANDS_H_


#include <G35.h>
#include <rf12.h>


// Program indexes on Controller
typedef enum
{
    CONTROLLER_PROGRAM_NULL                     = 0,
    CONTROLLER_PROGRAM_HOLLY                    = 1,
    CONTROLLER_PROGRAM_STROBE_BLUE              = 2,
    CONTROLLER_PROGRAM_STEPPED_WAVE             = 3,
    CONTROLLER_PROGRAM_METEORITE                = 4,
    CONTROLLER_PROGRAM_ICE                      = 5,
    CONTROLLER_PROGRAM_STROBE_RED               = 6,
    CONTROLLER_PROGRAM_RAINBOW_CHASE            = 7,
    CONTROLLER_PROGRAM_CANDY_CANE               = 8,
    CONTROLLER_PROGRAM_STROBE_GREEN             = 9,
    CONTROLLER_PROGRAM_FADE_IN_FADE_OUT         = 10,
    CONTROLLER_PROGRAM_STROBE_RAINBOW           = 11,
    CONTROLLER_PROGRAM_ALTERNATE_DIRECTION      = 12,
    CONTROLLER_PROGRAM_CHASE_RED_GREEN          = 13,
    CONTROLLER_PROGRAM_SOLID_RAINBOW            = 14,
    CONTROLLER_PROGRAM_PUMPKIN_BLINK            = 15,
    CONTROLLER_PROGRAM_SEAHAWKS                 = 16,
    CONTROLLER_PROGRAM_UW                       = 17,
    CONTROLLER_PROGRAM_DISSOLVE                 = 18,
    CONTROLLER_PROGRAM_CROSSOVERWAVE            = 19,

    CONTROLLER_PROGRAM_COUNT
} CONTROLLER_PROGRAMS;



// Program indexes on Node.
typedef enum
{
    COLOR_NODE_PROGRAM_SWITCH_OFF               = 0,
    COLOR_NODE_PROGRAM_RAW                      = 1,
    COLOR_NODE_PROGRAM_WHITES                   = 2,
    COLOR_NODE_PROGRAM_STEADY_MULTI             = 3,
    COLOR_NODE_PROGRAM_CROSS_OVER_WAVE          = 4,
    COLOR_NODE_PROGRAM_FORWARD_WAVE             = 5,
    COLOR_NODE_PROGRAM_ALTERNATE_DIRECTION_WAVE = 6,
    COLOR_NODE_PROGRAM_FADE_SINGLE_COLORS       = 7,
    COLOR_NODE_PROGRAM_BIDIRECTIONAL_WAVE       = 8,
    COLOR_NODE_PROGRAM_FADE_MULTI_COLORS        = 9,
    COLOR_NODE_PROGRAM_METEORITE                = 10,
    COLOR_NODE_PROGRAM_TWINKLE                  = 11,
    COLOR_NODE_PROGRAM_RAINBOW                  = 12,
    COLOR_NODE_PROGRAM_RANDOM_STROBE            = 13,

    COLOR_NODE_PROGRAM_RANDOM_FADE              = 14,
    COLOR_NODE_PROGRAM_CHASE                    = 15,
    COLOR_NODE_PROGRAM_SOLID                    = 16,
    COLOR_NODE_PROGRAM_WAVE                     = 17,
    COLOR_NODE_PROGRAM_STROBE_FILL              = 18,
    COLOR_NODE_PROGRAM_SHOOTING_STARS           = 19,
    COLOR_NODE_PROGRAM_DISSOLVE                 = 20,
    COLOR_NODE_PROGRAM_DRIP_FILL                = 21,

    COLOR_NODE_PROGRAM_TEST                     = 22,

    COLOR_NODE_PROGRAM_EYES                     = 23,


    COLOR_NODE_PROGRAM_COUNT
} COLOR_NODE_PROGRAMS;


// -----------------
// String Addressing
// -----------------
// Each string will have a unique ID and be associated with 1 or more groups.
// Strings can be addressed individually by ID or by their associated group.
// An option bit within the command will indicate the address type (group or id).
// The address field will be 16-bits.
//
// Group addressing enables multiple strings to be controlled by a single command.
// There are four groups (A, B, C, D).  Each group may address 16 strings.  Each
// string may be associated with any, all or no groups.


typedef enum
{
    ADDRESSED_AS_NONE   = 0,
    ADDRESSED_AS_ID     = 1,
    ADDRESSED_AS_GROUP  = 2,
} ADDRESSED_AS;


// String IDs.  Each string has a unique ID.
#define STRING_ID_WINDOW_BONUS      1
#define STRING_ID_WINDOW_LIVING     2
#define STRING_ID_ROOF_GARAGE_LEFT  3
#define STRING_ID_ROOF_GARAGE_RIGHT 4
#define STRING_ID_ROOF_BONUS_LEFT   5
#define STRING_ID_ROOF_BONUS_RIGHT  6
#define STRING_ID_ROOF_LIVING       7
#define STRING_ID_DOOR_SMALL        8
#define STRING_ID_DOOR_BIG          9
#define STRING_ID_DOOR_FRONT        10
#define STRING_ID_YARD_FRONT        11
#define STRING_ID_YARD_SIDE         12
#define STRING_ID_YARD_STRIP_FRONT  13 /* Not Used */
#define STRING_ID_YARD_STRIP_SIDE   14 /* Not Used */
#define STRING_ID_STAR              15
#define STRING_ID_SNOWFLAKE         16

#define STRING_ID_TREE_TOP          17
#define STRING_ID_TREE_BASE         18
#define STRING_ID_TREE_1            (STRING_ID_TREE_BASE + 0)   /* 18 */
#define STRING_ID_TREE_2            (STRING_ID_TREE_BASE + 1)   /* 19 */
#define STRING_ID_TREE_3            (STRING_ID_TREE_BASE + 2)   /* 20 */
#define STRING_ID_TREE_4            (STRING_ID_TREE_BASE + 3)   /* 21 */
#define STRING_ID_TREE_5            (STRING_ID_TREE_BASE + 4)   /* 22 */
#define STRING_ID_TREE_6            (STRING_ID_TREE_BASE + 5)   /* 23 */
#define STRING_ID_TREE_7            (STRING_ID_TREE_BASE + 6)   /* 24 */
#define STRING_ID_TREE_8            (STRING_ID_TREE_BASE + 7)   /* 25 */
#define STRING_ID_TREE_9            (STRING_ID_TREE_BASE + 8)   /* 26 */
#define STRING_ID_TREE_10           (STRING_ID_TREE_BASE + 9)   /* 27 */
#define STRING_ID_TREE_11           (STRING_ID_TREE_BASE + 10)  /* 28 */
#define STRING_ID_TREE_12           (STRING_ID_TREE_BASE + 11)  /* 29 */
#define STRING_ID_TREE_13           (STRING_ID_TREE_BASE + 12)  /* 30 */
#define STRING_ID_TREE_14           (STRING_ID_TREE_BASE + 13)  /* 31 */

#define STRING_ID_MINI_SNOWFLAKES   32
#define STRING_ID_SNOWFLAKE_2       33 /* Programmed as 16 for 2014 */
#define STRING_ID_ICICLES           34



// Valid string group IDs are 1 - 16
#define PACK_STRING_GROUP(__group)                  ( __group ? (((uint16_t)1) << (__group - 1)) : 0 )
#define IS_STRING_GROUP(__packed_group, __group)    ( (((uint16_t)__packed_group) & (PACK_STRING_GROUP(__group))) ? true : false )
#define STRING_GROUP_ALL                            (0xFFFF)

// String Group A
// This group is intended to include all strings.
#define STRING_GROUP_A_PROP         PACK_STRING_GROUP(1)
#define STRING_GROUP_A_WINDOW       PACK_STRING_GROUP(2)
#define STRING_GROUP_A_ROOF         PACK_STRING_GROUP(3)
#define STRING_GROUP_A_DOOR         PACK_STRING_GROUP(4)
#define STRING_GROUP_A_YARD         PACK_STRING_GROUP(5)
#define STRING_GROUP_A_TREE         PACK_STRING_GROUP(6)
#define STRING_GROUP_A_BUSHES       PACK_STRING_GROUP(7)

// String Group B
// This group contains all the strings of the mega tree.
#define STRING_GROUP_B_TREE_1       PACK_STRING_GROUP(1)
#define STRING_GROUP_B_TREE_2       PACK_STRING_GROUP(2)
#define STRING_GROUP_B_TREE_3       PACK_STRING_GROUP(3)
#define STRING_GROUP_B_TREE_4       PACK_STRING_GROUP(4)
#define STRING_GROUP_B_TREE_5       PACK_STRING_GROUP(5)
#define STRING_GROUP_B_TREE_6       PACK_STRING_GROUP(6)
#define STRING_GROUP_B_TREE_7       PACK_STRING_GROUP(7)
#define STRING_GROUP_B_TREE_8       PACK_STRING_GROUP(8)
#define STRING_GROUP_B_TREE_9       PACK_STRING_GROUP(9)
#define STRING_GROUP_B_TREE_10      PACK_STRING_GROUP(10)
#define STRING_GROUP_B_TREE_11      PACK_STRING_GROUP(11)
#define STRING_GROUP_B_TREE_12      PACK_STRING_GROUP(12)
#define STRING_GROUP_B_TREE_13      PACK_STRING_GROUP(13)
#define STRING_GROUP_B_TREE_14      PACK_STRING_GROUP(14)
#define STRING_GROUP_B_TREE_TOP     PACK_STRING_GROUP(15)
#define STRING_GROUP_B_TREE_TRUNK   PACK_STRING_GROUP(16)

#define TREE_LEG_COUNT 14


// String Group C
// This group contains all snowflakes.
#define STRING_GROUP_C_SNOWFLAKE_1  PACK_STRING_GROUP(1)
#define STRING_GROUP_C_SNOWFLAKE_2  PACK_STRING_GROUP(2)


// String Group D
// Unused


// size = 8 bytes
typedef struct
{
    uint16_t address;
    uint8_t sequence;
    uint8_t type;
    uint8_t option;
    uint8_t layout;
    uint16_t seed;
} Command;

#define COMMAND_OPTION_NONE         0x00
#define COMMAND_OPTION_DEFER        0x01    /* defer processing until commit is received */
#define COMMAND_OPTION_UPDATE       0x02    /* update current command */
#define COMMAND_OPTION_ACKNOWLEDGE  0x04    /* controller requests an ack */
#define COMMAND_OPTION_RESERVED     0x08    /* Undefined */
#define COMMAND_OPTION_GROUP_A      0x10    /* group A addressing */
#define COMMAND_OPTION_GROUP_B      0x20    /* group B addressing */
#define COMMAND_OPTION_GROUP_C      0x40    /* group C addressing */
#define COMMAND_OPTION_GROUP_D      0x80    /* group D addressing */

#define COMMAND_OPTION_GROUP_MASK   (0xF0)

#define STRING_GROUP_COUNT (4)


// Random Seed
// The Command.seed enables the controller to control the RNG of each node.
// There are two reserved values, described below.  Any other value is used
// as the new seed.
#define RANDOM_SEED_PRESERVE    (0)         /* preserve the current seed */
#define RANDOM_SEED_RESET       (0xFFFF)    /* reset seed with a new random seed */


// size = 13 bytes
typedef struct
{
    Command command;
    uint8_t program;    // program index to run
    uint8_t pattern;    // pattern to pass to program (this is specifically not using pattern_t so as not to change the data packet size)
    uint8_t option;     // option to pass to pattern
    uint16_t delay;     // pattern delay in milliseconds (this is specifically not using delay_t so as not to change the data packet size)
} ProgramCommand;

// size = 13 + 50 = 63 bytes
typedef struct
{
    Command command;
    uint8_t start_bulb;     // starting bulb
    uint8_t end_bulb;       // ending bulb
    uint8_t intensity;      // intensity of each bulb
    uint16_t bulb_delay;    // delay between bulbs (this is specifically not using delay_t so as not to change the data packet size)
} RawCommand;

// size = 16 bytes
typedef struct
{
    Command command;
    uint8_t string_id;
    uint8_t string_groups[STRING_GROUP_COUNT];
    uint8_t rf_node;
    uint8_t rf_group;
    uint8_t rf_controller;
} ConfigAddressCommand;

// size = 11 bytes
typedef struct
{
    Command command;
    uint8_t physicalCount;
    uint8_t logicalCount;
    uint8_t enumerationDirection; // 1 = forward, 0 = backward
    uint16_t enumerationDelay;  // ms to wait before enumerating bulbs
} ConfigLightStringCommand;

/*
// size = 22 bytes
typedef struct
{
    Command command;
    uint8_t version;
    uint8_t string_id;
    uint8_t string_groups[STRING_GROUP_COUNT];
    uint8_t rf_node;
    uint8_t rf_group;
    uint8_t rf_controller;
    uint8_t physicalCount;
    uint8_t logicalCount;
    uint8_t enumerationDirection;
    uint16_t enumerationDelay;
} QueryResponse;
*/

typedef enum
{
    COMMAND_OFF     = 0,
    COMMAND_PROGRAM = 1,
    COMMAND_RAW     = 2,
    COMMAND_COMMIT  = 3,
    COMMAND_KICK    = 4,
    COMMAND_ADDRESS_CONFIG = 5,
    COMMAND_LIGHTSTRING_CONFIG = 6,
    //COMMAND_QUERY   = 7,
    //COMMAND_QUERY_RESPONSE = 8
} COMMAND_TYPE;

#define COMMAND_MIN COMMAND_OFF
#define COMMAND_MAX COMMAND_LIGHTSTRING_CONFIG

typedef enum
{
    COLOR_NODE_CONTROLLER   = 0,
    COLOR_NODE_NODE         = 1
} COLOR_NODE_TYPE;


#define MAX_LIGHTS          (50)
#define MAX_COMMAND_BUFFER  (sizeof(RawCommand) + MAX_LIGHTS)


// EEPROM Configuration Offsets
#define EEPROM_RF_NODE_ID               0
#define EEPROM_RF_GROUP_ID              1
#define EEPROM_RF_CONTROLLER_ID         2
#define EEPROM_PHYSICAL_COUNT           3
#define EEPROM_LOGICAL_COUNT            4
#define EEPROM_ENUMERATION_DIRECTION    5
#define EEPROM_STRING_ID                6
#define EEPROM_STRING_GROUPS            7
//                      GROUP A         7
//                      GROUP B         8
//                      GROUP C         9
//                      GROUP D         10
#define EEPROM_ENUMERATION_DELAY        11
//                      Low Byte        11
//                      High Byte       12



#endif

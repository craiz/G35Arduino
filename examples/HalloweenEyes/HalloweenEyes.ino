//*********************************************************************
//* Halloween Spooky Eyes Controller
//* by Paul Irwin
//* September 25, 2014
//*
//* This sketch is designed to manage a "Hedge Monster" halloween
//* decoration and a string of lights.  Each light is operated
//* as a set of spookky eyes built using PVC pipe with holes cut for
//* eyes.
//*
//* A motion detection sensor (PIR) is used to trigger angery and waiting states.
//* When Angry, the hedge monster is active and all eyes are red.
//* When Waiting, the hedge monster is inactive and eyes are blinking/watching.
//*
//* Note: The pin configuration is set up for use with a
//*       ColorNode v1.1 board.
//*********************************************************************


#define DEBUG_ENABLED 1
#if DEBUG_ENABLED
#include <Debug.h>
#include <SerialPrintf.h>
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif


#include <RF12.h>
#include <G35String.h>
#include <LightProgram.h>
#include <ProgramRunner.h>
#include <SerialPrintf.h>
#include <SpookyEyes.h>
#include <Solid.h>
#include <MEOSwitchOff.h>
#include <ColorUtils.h>


//*********************************************************************

#define G35_PIN             19 /*17*/  /* LED/17 */
#define HEDGE_MONSTER_PIN    9  /* D9 */
#define MOTION_SENSOR_PIN    8  /* D8 */
#define LED_DEBUG_PIN        3

#define PHYSICAL_LIGHT_COUNT_DEFAULT    16
#define LOGICAL_LIGHT_COUNT_DEFAULT     16
#define ENUMERATION_DIRECTION_DEFAULT    1  // forward
#define ENUMERATION_DELAY_DEFAULT       50

G35String lights;

//*********************************************************************
// Interface for program runner

LightProgram* CreateProgram(uint8_t programIndex)
{
    return new SpookyEyes(lights);
}

ProgramRunner runner(CreateProgram, 1);

#define PEACEFUL_TIME_BASE      5000
#define PEACEFUL_TIME_RANDOM    5000
#define ANGER_TIME_BASE         4000
#define ANGER_TIME_RANDOM       10000
#define EYE_RESET_TIME          1000


//*********************************************************************
//* Setup Function
void setup()
{
    // Start the UART
#if DEBUG_ENABLED
    Serial.begin(57600);
#endif
    DebugPrintf("Halloween Eyes\n");

    DebugPrintf("PEACEFUL_TIME_BASE: %u\n", PEACEFUL_TIME_BASE);
    DebugPrintf("PEACEFUL_TIME_RANDOM: %u\n", PEACEFUL_TIME_RANDOM);
    DebugPrintf("ANGER_TIME_BASE: %u\n", ANGER_TIME_BASE);
    DebugPrintf("ANGER_TIME_RANDOM: %u\n", ANGER_TIME_RANDOM);

    // Configure pins
    DebugPrintf("HEDGE_MONSTER_PIN: %u\n", HEDGE_MONSTER_PIN);
    DebugPrintf("MOTION_SENSOR_PIN: %u\n", MOTION_SENSOR_PIN);
    DebugPrintf("LED_DEBUG_PIN: %u\n", LED_DEBUG_PIN);
    DebugPrintf("G35_PIN: %u\n", G35_PIN);
    pinMode(HEDGE_MONSTER_PIN, OUTPUT);
    pinMode(MOTION_SENSOR_PIN, INPUT);
    pinMode(LED_DEBUG_PIN, OUTPUT);

    lights.Configure(G35_PIN, PHYSICAL_LIGHT_COUNT_DEFAULT, LOGICAL_LIGHT_COUNT_DEFAULT, (bool)ENUMERATION_DIRECTION_DEFAULT, STRING_LAYOUT_LINEAR);

    // Seed random number generator.
    srand(analogRead(0));

    // Initialize light string
    delay(ENUMERATION_DELAY_DEFAULT);
    lights.enumerate();
    delay(50);

    //lights.do_test_patterns();

    runner.SetAutoAdvanceEnabled(false);
    runner.SwitchProgram(0, 0, 0, 0);

    // Give motion sensor some time to settle.
    delay(5000);
}


bool fCurrentlyAngry = false;
uint32_t nextCalmTime = 0;      // time to calm down if no object
uint32_t nextAngryTime = 0;     // time when next anger is allowed

bool fLastObjectDected = false;

//*********************************************************************
//* Main Loop
void loop()
{
    uint32_t now;
    bool fObjectDected = false;

    // Get the current time
    now = millis();
    
    // Detect motion
    fObjectDected = (digitalRead(MOTION_SENSOR_PIN) == HIGH);
    if (fObjectDected != fLastObjectDected)
    {
        fLastObjectDected = fObjectDected;
        DebugPrintf("Object State Changed: %u, %lu\n", fObjectDected, now);
        digitalWrite(LED_DEBUG_PIN, fObjectDected);
    }

    // Anger management
    if (fCurrentlyAngry)
    {
        // check if it's time to calm down (angry time expired or no object)
        if (!fObjectDected || now >= nextCalmTime)
        {
            // Make sure we don't get angry again too soon
            nextAngryTime = now + PEACEFUL_TIME_BASE + (rand() % PEACEFUL_TIME_RANDOM);
            fCurrentlyAngry = false;
            DebugPrintf("Calming Down! %lu \n", now);
            DebugPrintf("nextAngryTime = %lu \n", nextAngryTime);

            // Turn off hedge monster
            digitalWrite(HEDGE_MONSTER_PIN, LOW);

            // Let eyes relax and return to normal blinking.
            runner.UpdateProgram(0, SpookyEyes::CALM, 0, 0);
        }
    }
    else
    {
        // check if something has made us angry
        if (fObjectDected && now > nextAngryTime)
        {
            // Track new anger state
            nextCalmTime = now + ANGER_TIME_BASE + (rand() % ANGER_TIME_RANDOM);
            fCurrentlyAngry = true;
            DebugPrintf("Getting Angry! %lu \n", now);
            DebugPrintf("nextCalmTime = %lu\n", nextCalmTime);

            // Turn on hedge monster
            digitalWrite(HEDGE_MONSTER_PIN, HIGH);

            // Make eyes "mad" by turning them all red.
            runner.UpdateProgram(0, SpookyEyes::ANGRY, 0, 0);
        }
    }

    runner.loop();
}


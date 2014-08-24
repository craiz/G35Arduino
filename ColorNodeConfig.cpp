#include <DebugConfig.h>
#if DEBUG_CONFIG
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif


#include <RF12.h>
#include <ColorNodeConfig.h>
#include <ColorNodeCommands.h>


void ShowNodeConfiguration(byte nodeType, byte rfNodeId, byte rfGroupId, byte rfControllerId, byte frequency)
{
    DebugPrintf("[GE Color Effects %s]\n", nodeType == COLOR_NODE_CONTROLLER ? "Controller" : "Node");
    DebugPrintf("  RFNodeID: %u\n", rfNodeId);
    DebugPrintf("  RFGroup: %u\n", rfGroupId);

// The frequency is not currently configurable
#if 0
    switch (freq)
    {
        case RF12_433MHZ:
        {
            DebugPrintf("  Freq: 433MHz\n");
            break;
        }
        case RF12_868MHZ:
        {
            DebugPrintf("  Freq: 868MHz\n");
            break;
        }
        case RF12_915MHZ:
        {
            DebugPrintf("  Freq: 915MHz\n");
            break;
        }
        default:
        {
            DebugPrintf("  Freq: Unknown (%u)\n", freq);
            break;
        }
    }
#else
    DebugPrintf("  Freq. 433MHz\n");
#endif

    if (nodeType == COLOR_NODE_NODE)
    {
        DebugPrintf("  RFControllerID: %u\n", rfControllerId);
    }
}

void ShowStringConfiguration(byte stringId, byte* pStringGroups, byte stringType, byte physicalLightCount, byte logicalLightCount, byte enumerationDirection, uint16_t enumerationDelay)
{
    DebugPrintf("  String ID: %u\n", stringId);
#if DEBUG_ENABLED
    for (uint8_t i = 0; i < STRING_GROUP_COUNT; i++)
    {
        DebugPrintf("  String Group %c: %u - 0x%04x\n", 'A' + i, pStringGroups[i], PACK_STRING_GROUP(pStringGroups[i]));
    }
#endif
    DebugPrintf("  String Type: %u\n", stringType);
    DebugPrintf("  Lights: %u %u\n", physicalLightCount, logicalLightCount);
    DebugPrintf("  Direction: %s\n", (bool)enumerationDirection ? "Forward" : "Backward");
    DebugPrintf("  Delay: %u\n", enumerationDelay);
}


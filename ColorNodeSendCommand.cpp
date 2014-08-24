
#include <DebugConfig.h>
#if DEBUG_SEND_COMMAND
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <ColorNodeSendCommand.h>
#include <RF12.h>

byte payloadData[MAX_COMMAND_BUFFER];
uint8_t payloadSize = 0;
uint8_t payloadSequence = 0;


void SendCommand()
{
    SendCommand(SEND_COMMAND_RETRIES_DEFAULT, SEND_COMMAND_RETRY_DELAY_DEFAULT);
}


void SendCommand(uint8_t retries, uint16_t delay)
{
#if 1
    Command * command = (Command *)payloadData;
    command->sequence = payloadSequence++;

    DebugPrintf("Sending Command\n");
    DebugPrintf("  Address: 0x%04x\n", command->address);
    DebugPrintf("  Sequence: %u\n", command->sequence);
    DebugPrintf("  Type: %u\n", command->type);
    DebugPrintf("  Layout: 0x%02x\n", command->layout);
    DebugPrintf("  Seed: 0x%04x\n", command->seed);
    DebugPrintf("  Option: 0x%02x\n", command->option);
    DebugPrintf("  Size: %u\n", payloadSize);

    if (payloadSize <= MAX_COMMAND_BUFFER)
    {
        rf12_easyConfig(retries, delay);
        rf12_easySend(payloadData, payloadSize);
        char rfStatus = -1;
        while (rfStatus == -1)
        {
            rfStatus = rf12_easyPoll();
        }
        
        DebugPrintf("Command Sent\n");
        DebugPrintf("  Status: %d\n", rfStatus);
        DebugPrintf("  HDR CTL: 0x%02x\n", rf12_hdr & RF12_HDR_CTL);
        DebugPrintf("  HDR DST: 0x%02x\n", rf12_hdr & RF12_HDR_DST);
        DebugPrintf("  HDR ACK: 0x%02x\n", rf12_hdr & RF12_HDR_ACK);
        DebugPrintf("  HDR NODE: 0x%02x\n", rf12_hdr & RF12_HDR_MASK);
    }
    else
    {
        DebugPrintf("Payload too big! (max=%u)\n", MAX_COMMAND_BUFFER);
    }
#endif
}


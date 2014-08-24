#ifndef _COLOR_NODE_SEND_COMMAND_H_
#define _COLOR_NODE_SEND_COMMAND_H_

#include <ColorNodeCommands.h>

#define SEND_COMMAND_RETRIES_DEFAULT        5
#define SEND_COMMAND_RETRY_DELAY_DEFAULT    20


void SendCommand();
void SendCommand(uint8_t retries, uint16_t delay);


// It's not ideal to use globals, but the command payload requires a large data buffer so
// the most efficient way to manage it is to use a shared global buffer.
extern byte payloadData[MAX_COMMAND_BUFFER];
extern uint8_t payloadSize;
extern uint8_t payloadSequence;

#endif // _COLOR_NODE_SEND_COMMAND_H_


#ifndef _RF12_H_
#define _RF12_H_

#include <Arduino.h>

char rf12_easyPoll(void);
char rf12_easySend(const void* data, uint8_t size);

#endif // _RF12_H_
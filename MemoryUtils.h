
// MemoryFree library based on code posted here:
// http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1213583720/15
// 
// Extended by Matthew Murdoch to include walking of the free list.
#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H


#include <Arduino.h>


#ifdef __cplusplus
extern "C" {
#endif
int freeMemory();
#ifdef  __cplusplus
}
#endif


void check_mem();
void printf_mem();

void memCheck();

#endif // MEMORY_UTILS_H


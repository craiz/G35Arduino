#ifndef _SERIAL_PRINTF_H_
#define _SERIAL_PRINTF_H_

#include <Ports.h>
#include <stdio.h>
#include <stdarg.h>
#include <avr/pgmspace.h>

void _SerialPrintf(const char *fmt, ...);

#define SerialPrintf(fmt, ...) _SerialPrintf(PSTR(fmt), ##__VA_ARGS__)

#endif //_SERIAL_PRINTF_H_
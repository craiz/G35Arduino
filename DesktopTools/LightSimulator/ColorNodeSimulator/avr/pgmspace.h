#ifndef _PGMSPACE_H_
#define _PGMSPACE_H_

#include <Arduino.h>

#define PROGMEM

typedef uint8_t prog_uchar;


#define   pgm_read_byte(_address_short) (*_address_short)

#endif // _PGMSPACE_H_
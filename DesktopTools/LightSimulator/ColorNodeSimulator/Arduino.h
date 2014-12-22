#ifndef _ARDUINO_H_
#define _ARDUINO_H_

#include <Windows.h>
#include <stdio.h>
#include <complex> // for math (sin, et)

// Types
typedef unsigned char uint8_t;
typedef unsigned char byte;
typedef char int8_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned uint32_t;
//typedef float gradient_t;

// Random stuff
#define OUTPUT 0
#define HIGH 1
#define LOW 0
#define pinMode(x, y)
#define interrupts()
#define noInterrupts()
#define digitalWrite(x, y)
#define delayMicroseconds(x)
#define PI 3.14

#ifdef RGB
#undef RGB
#endif

uint32_t millis();

void delay(uint16_t ms);

#endif // _ARDUINO_H_
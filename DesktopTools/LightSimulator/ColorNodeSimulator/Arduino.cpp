#include "Arduino.h"

void delay(uint16_t ms)
{
    HANDLE h = CreateEventEx(NULL, NULL, CREATE_EVENT_MANUAL_RESET, EVENT_ALL_ACCESS);
    WaitForSingleObjectEx(h, ms, FALSE);
	//Sleep(ms);
}

uint32_t millis()
{
    ULONGLONG ticks = GetTickCount64();
    return (uint32_t)ticks;
	//return GetTickCount();
}

#include <Arduino.h>
#include <ColorNodeUtils.h>


unsigned long now()
{
    // FIXME 49-day overflow
    return millis() / 1000;
}

void sleep(unsigned long milliseconds)
{
    delay(milliseconds);
}


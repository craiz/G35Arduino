/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.

  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  Original version by Paul Martis (http://www.digitalmisery.com). See
  README for complete attributions.

  Special thanks to Richard <rkfoote@gmail.com> and "slinky" for the unrolled-
  loop protocol code that seems to work very well!
*/

#include <DebugConfig.h>
#if DEBUG_G35
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <G35String.h>

#define MHZ_16 (1)  // standard Arduino/Teensy

#if MHZ_16
#define DELAYLONG 17    // should be ~ 20uS long
#define DELAYSHORT 7   // should be ~ 10uS long
#else  // 20MHz
#define DELAYLONG 25    // should be ~ 20uS long
#define DELAYSHORT 11   // should be ~ 10uS long
#endif
#define DELAYEND 40     // should be ~ 30uS long

#define ZERO(x) digitalWrite(x, LOW);           \
  delayMicroseconds(DELAYSHORT);                \
  digitalWrite(x, HIGH);                        \
  delayMicroseconds(DELAYLONG);

#define ONE(x) digitalWrite(x, LOW);            \
  delayMicroseconds(DELAYLONG);                 \
  digitalWrite(x, HIGH);                        \
  delayMicroseconds(DELAYSHORT);

G35String::G35String()
  : G35()
  , pin_(0)
  , physical_light_count_(0)
  , bulb_zero_(0)
  , is_forward_(true)
  , layout_(STRING_LAYOUT_DEFAULT)
{
}

void G35String::Configure(uint8_t pin, light_count_t physical_light_count,
                     light_count_t logical_light_count, bool is_forward,
                     STRING_LAYOUT layout)
{
    pin_ = pin;
    physical_light_count_ = physical_light_count;
    light_count_ = logical_light_count;
    is_forward_ = is_forward;
    layout_ = layout;
    pinMode(pin, OUTPUT);
}

void G35String::set_color(light_count_t bulb, uint8_t intensity, color_t color)
{
    if (bulb != BROADCAST_BULB)
    {
        bulb += bulb_zero_;
    }
    uint8_t r, g, b;
    r = color & 0x0F;
    g = (color >> 4) & 0x0F;
    b = (color >> 8) & 0x0F;

    DebugPrintf("SetColor Bulb: %d, Intensity: %d, Color: %d,%d,%d\n", bulb, intensity, r, g, b);

    if (intensity > MAX_INTENSITY)
    {
        intensity = MAX_INTENSITY;
    }

    noInterrupts();

    digitalWrite(pin_, HIGH);
    delayMicroseconds(DELAYSHORT);

    // LED Address
    if (bulb & 0x20) { ONE(pin_); } else { ZERO(pin_); }
    if (bulb & 0x10) { ONE(pin_); } else { ZERO(pin_); }
    if (bulb & 0x08) { ONE(pin_); } else { ZERO(pin_); }
    if (bulb & 0x04) { ONE(pin_); } else { ZERO(pin_); }
    if (bulb & 0x02) { ONE(pin_); } else { ZERO(pin_); }
    if (bulb & 0x01) { ONE(pin_); } else { ZERO(pin_); }

    // Brightness
    if (intensity & 0x80) { ONE(pin_); } else { ZERO(pin_); }
    if (intensity & 0x40) { ONE(pin_); } else { ZERO(pin_); }
    if (intensity & 0x20) { ONE(pin_); } else { ZERO(pin_); }
    if (intensity & 0x10) { ONE(pin_); } else { ZERO(pin_); }
    if (intensity & 0x08) { ONE(pin_); } else { ZERO(pin_); }
    if (intensity & 0x04) { ONE(pin_); } else { ZERO(pin_); }
    if (intensity & 0x02) { ONE(pin_); } else { ZERO(pin_); }
    if (intensity & 0x01) { ONE(pin_); } else { ZERO(pin_); }

    // Blue
    if (b & 0x8) { ONE(pin_); } else { ZERO(pin_); }
    if (b & 0x4) { ONE(pin_); } else { ZERO(pin_); }
    if (b & 0x2) { ONE(pin_); } else { ZERO(pin_); }
    if (b & 0x1) { ONE(pin_); } else { ZERO(pin_); }

    // Green
    if (g & 0x8) { ONE(pin_); } else { ZERO(pin_); }
    if (g & 0x4) { ONE(pin_); } else { ZERO(pin_); }
    if (g & 0x2) { ONE(pin_); } else { ZERO(pin_); }
    if (g & 0x1) { ONE(pin_); } else { ZERO(pin_); }

    // Red
    if (r & 0x8) { ONE(pin_); } else { ZERO(pin_); }
    if (r & 0x4) { ONE(pin_); } else { ZERO(pin_); }
    if (r & 0x2) { ONE(pin_); } else { ZERO(pin_); }
    if (r & 0x1) { ONE(pin_); } else { ZERO(pin_); }

    digitalWrite(pin_, LOW);
    delayMicroseconds(DELAYEND);

    interrupts();
}

void G35String::enumerate()
{
    enumerate(is_forward_);
}

void G35String::enumerate(bool forward)
{
    light_count_t count = physical_light_count_;
    light_count_t bulb = forward ? 0 : physical_light_count_ - 1;
    int8_t delta = forward ? 1 : -1;
    bulb_zero_ = 0;
    while (count--)
    {
        set_color(bulb, MAX_INTENSITY, COLOR_BLACK);
        bulb += delta;
    }

    // Set logical bulb_zero past the unused physical bulbs when running in forward enumeration.
    if (forward && (physical_light_count_ > light_count_))
    {
        bulb_zero_ = physical_light_count_ - light_count_;
        DebugPrintf("bulb_zero_ = %u\n", bulb_zero_);
    }
}

void G35String::enumerate_forward()
{
    enumerate(true);
}

void G35String::enumerate_reverse()
{
    enumerate(false);
}

#if 0
// New Test Pattern
void G35String::do_test_patterns() {
  const uint8_t last_light = light_count_ - 1;

  // Cycle through primaries.
  fill_color(0, light_count_, MAX_INTENSITY, COLOR_RED);
  delay(1000);
  fill_color(0, light_count_, MAX_INTENSITY, COLOR_GREEN);
  delay(1000);
  fill_color(0, light_count_, MAX_INTENSITY, COLOR_BLUE);
  delay(1000);

  // Tickle the ends. You should see three reds at the start, and three greens
  // at the end. This confirms that you've properly configured the strand
  // lengths and directions.
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 3; ++j) {
      set_color(BROADCAST_BULB, 0, COLOR_BLACK);
      set_color(j, MAX_INTENSITY, COLOR_RED);
      set_color(last_light - j, MAX_INTENSITY, COLOR_GREEN);
      delay(250);
    }
  }

  // Full white for five seconds. If you have power problems, they'll probably
  // show up here.
  fill_color(0, light_count_, MAX_INTENSITY, COLOR_WHITE);
  delay(5000);

  // Cycle through secondaries.
  fill_color(0, light_count_, MAX_INTENSITY, COLOR_YELLOW);
  delay(1000);
  fill_color(0, light_count_, MAX_INTENSITY, COLOR_CYAN);
  delay(1000);
  fill_color(0, light_count_, MAX_INTENSITY, COLOR_MAGENTA);
  delay(1000);

  // ... and get ready for the first program.
  fill_color(0, light_count_, MAX_INTENSITY, COLOR_BLACK);
}
#else
// Old Test Pattern
void G35String::do_test_patterns()
{
    const light_count_t d = 1000 / light_count_;
    const light_count_t last_light = light_count_ - 1;
    fill_sequence(0, light_count_, 0, 1, 0, rainbow_color);

    for (uint8_t i = 0; i <= MAX_INTENSITY; ++i)
    {
        set_color(BROADCAST_BULB, i, COLOR_BLACK);
        delay(1);
    }

    delay(500);

    for (int i = MAX_INTENSITY; i >= 0; --i)
    {
        set_color(BROADCAST_BULB, i, COLOR_BLACK);
        delay(1);
    }

    for (light_count_t i = 0; i < light_count_; ++i)
    {
        set_color(i, MAX_INTENSITY, COLOR_GREEN);
        set_color(last_light - i, MAX_INTENSITY, COLOR_BLUE);
        if (i > 0)
        {
            set_color(i - 1, MAX_INTENSITY, COLOR_BLACK);
            set_color(last_light - i + 1, MAX_INTENSITY, COLOR_BLACK);
        }
        delay(d);
    }

    fill_color(0, light_count_, MAX_INTENSITY, COLOR_BLACK);
}
#endif

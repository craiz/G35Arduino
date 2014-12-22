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

color_t *g_colors = NULL;


G35String::G35String()
: G35(), pin_(0), physical_light_count_(0),
  bulb_zero_(0), is_forward_(true), layout_(STRING_LAYOUT_DEFAULT)
{
}

void G35String::Configure(uint8_t pin, light_count_t light_count,
                     light_count_t physical_light_count,
                     bool is_forward,
                     STRING_LAYOUT layout)
{
    pin_ = pin;
    physical_light_count_ = physical_light_count;
    bulb_zero_ = physical_light_count - light_count;
    is_forward_ = is_forward;
    pinMode(pin, OUTPUT);
    light_count_ = light_count;
    layout_ = layout;

    if (g_colors)
    {
        delete [] g_colors;
    }
    g_colors = new color_t[physical_light_count_];
    memset(g_colors, 0, sizeof(color_t) * physical_light_count_);
}

void G35String::set_color(light_count_t bulb, uint8_t intensity, color_t color)
{
    color_t color2 = 0;

    for (int i = 0; i < 3; i++)
    {
        color2 = color2 << 4;
        color2 = color2 | (color & 0xf);
        color = color >> 4;
    }
    
    g_colors[bulb] = color2;
}

color_t get_color(light_count_t bulb)
{
    return g_colors[bulb];
}

void G35String::enumerate() {
  enumerate(is_forward_);
}

void G35String::enumerate(bool forward) {
  light_count_t count = physical_light_count_;
  light_count_t bulb = forward ? 0 : light_count_ - 1;
  int8_t delta = forward ? 1 : -1;
  while (count--) {
    set_color(bulb, MAX_INTENSITY, COLOR_BLACK);
    bulb += delta;
  }
}

void G35String::enumerate_forward() {
  enumerate(true);
}

void G35String::enumerate_reverse() {
  enumerate(false);
}

void G35String::do_test_patterns() {
  const light_count_t d = 1000 / light_count_;
  const light_count_t last_light = light_count_ - 1;
  fill_sequence(0, light_count_, 0, 1, 0, rainbow_color);

  for (uint8_t i = 0; i <= MAX_INTENSITY; ++i) {
    set_color(BROADCAST_BULB, i, COLOR_BLACK);
    delay(1);
  }

  delay(500);

  for (int i = MAX_INTENSITY; i >= 0; --i) {
    set_color(BROADCAST_BULB, i, COLOR_BLACK);
    delay(1);
  }

  for (light_count_t i = 0; i < light_count_; ++i) {
    set_color(i, MAX_INTENSITY, COLOR_GREEN);
    set_color(last_light - i, MAX_INTENSITY, COLOR_BLUE);
    if (i > 0) {
      set_color(i - 1, MAX_INTENSITY, COLOR_BLACK);
      set_color(last_light - i + 1, MAX_INTENSITY, COLOR_BLACK);
    }
    delay(d);
  }

  fill_color(0, light_count_, MAX_INTENSITY, COLOR_BLACK);
}

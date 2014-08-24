/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  Original version by Paul Martis (http://www.digitalmisery.com). See
  README for complete attributions.
*/

#ifndef INCLUDE_G35_STRING_H
#define INCLUDE_G35_STRING_H

#include <G35.h>

typedef enum 
{
    STRING_LAYOUT_DEFAULT                   =  0,

    // General layouts
    STRING_LAYOUT_LINEAR                    =  1,   // Normal linear string of bulbs
    STRING_LAYOUT_SIDES                     =  2,   // Each logical side is a group of bulbs
    STRING_LAYOUT_HORIZONTAL_LINES          =  3,   // Bulbs are grouped into horizontal lines.
    STRING_LAYOUT_HORIZONTAL_LINES_CENTER   =  5,   // Bulbs are grouped into horzontal lines originating from the center.
    STRING_LAYOUT_VERTICAL_LINES            =  4,   // Bulbs are grouped into vertical lines.
    STRING_LAYOUT_VERTICAL_LINES_CENTER     =  6,   // Bulbs are grouped into vertical lines originating from the center.
    STRING_LAYOUT_RINGS_CENTER              =  7,   // Bulbs are grouped in concentric rings originating from the center
    STRING_LAYOUT_RINGS_CORNER              =  8,   // Bulbs are grouped in concentric rings originating from the corners

    // Star Layouts
    STRING_LAYOUT_STAR_RINGS                =  9,
    STRING_LAYOUT_STAR_BLADES               = 10,
    STRING_LAYOUT_STAR_WINGS                = 11,
    STRING_LAYOUT_STAR_SIDES                = 12,
    STRING_LAYOUT_STAR_LINES                = 13,

    // Snowflake Modes
    STRING_LAYOUT_SNOWFLAKE_RINGS           = 14,
    STRING_LAYOUT_SNOWFLAKE_BLADES          = 15,
    STRING_LAYOUT_SNOWFLAKE_LINES           = 16,

    // Tree Top Modes
    STRING_LAYOUT_TREE_TOP_DOWN_LEFT_TO_RIGHT = 17,
    STRING_LAYOUT_TREE_TOP_UP_LEFT_TO_RIGHT   = 18,
    STRING_LAYOUT_TREE_TOP_DOWN_RIGHT_TO_LEFT = 19,
    STRING_LAYOUT_TREE_TOP_UP_RIGHT_TO_LEFT   = 20,

    STRING_LAYOUT_COUNT
} STRING_LAYOUT;


// A G35String knows how to talk to a real GE Color Effects light string.
// In particular, it implements the set_color() method of the G35 interface.
//
// These strings need enumerate() to be called before anything else, so that
// each bulb has an individual address. In many cases, your lights will work
// as expected even if you forget to call enumerate(), because most programs
// happen to do the same thing as enumerate() -- namely, they send commands
// to all bulbs starting with bulb #0 and ending with bulb #N-1. If your
// light programs look right but fractured, it's because you forgot to call
// enumerate().
class G35String : public G35 {
 public:
  // |pin|: the Arduino pin driving this string's data line.
  // |light_count|: the number of visible, physical bulbs on the string.
  // |physical_light_count|: the number of physical bulbs on the string.
  // |bulb_zero|: the index of the first bulb (almost always zero).
  // |is_forward|: true if the closest bulb to the plug has the lowest index.
  G35String();
  virtual void Configure(uint8_t pin, light_count_t physical_light_count, light_count_t logical_light_count,
            bool is_forward, STRING_LAYOUT layout);


  // Implementation of G35 interface.
  virtual light_count_t get_light_count() { return light_count_; }
  virtual void set_light_count(light_count_t light_count) { light_count_ = light_count; }
  virtual void set_color(light_count_t bulb, uint8_t intensity, color_t color);

  virtual STRING_LAYOUT get_layout() { return layout_; };
  virtual void set_layout(STRING_LAYOUT layout) { layout_ = layout; };

  // Initialize lights by giving them each an address.
  void enumerate();

  // Displays known-good patterns. Useful to prevent insanity during hardware
  // debugging.
  void do_test_patterns();

 protected:
  virtual uint8_t get_broadcast_bulb() { return BROADCAST_BULB; }

  STRING_LAYOUT layout_;

 private:
  uint8_t pin_;
  light_count_t physical_light_count_;
  light_count_t bulb_zero_;
  bool is_forward_;

  enum {
    MAX_INTENSITY = 0xcc,
    BROADCAST_BULB = 63,
  };

  // Initialize lights by giving them each an address. enumerate_forward()
  // numbers the bulb closest to the controller 0, and enumerate_reverse()
  // numbers the farthest bulb 0.
  void enumerate(bool reverse);
  void enumerate_forward();
  void enumerate_reverse();
};

#endif  // INCLUDE_G35_STRING_H

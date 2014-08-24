/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_PROGRAMS_ORBIT_H
#define INCLUDE_G35_PROGRAMS_ORBIT_H

#include <LightProgram.h>
#include <Orbiter.h>

class Orbit : public LightProgram
{
public:
    Orbit(G35& g35);
    bool Initialize(pattern_t pattern, option_t option, delay_t delay);
    uint32_t Do();

protected:
    Orbit(G35& g35, bool should_erase);

private:
    enum { MAX_OBJECTS = 10 };
    bool should_erase_;
    light_count_t count_;
    light_count_t light_count_;
    Orbiter orbiter_[MAX_OBJECTS];
    light_count_t orbiter_center_[MAX_OBJECTS];
    light_count_t last_x_[MAX_OBJECTS];

    void set_centers();
};

class OrbitSmudge : public Orbit
{
public:
    OrbitSmudge(G35& g35);
};

#endif  // INCLUDE_G35_PROGRAMS_ORBIT_H

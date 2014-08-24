/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  See README for complete attributions.
*/

#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_ORBIT
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <Orbit.h>


Orbit::Orbit(G35& g35)
  : LightProgram(g35),
    should_erase_(true),
    count_(MAX_OBJECTS),
    light_count_(g35_.get_light_count())
{
    DebugPrintf("Orbit\n");

    delay_default_ = g35_.get_bulb_frame() >> 1;
}

bool Orbit::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    LightProgram::Initialize(pattern, option, delay);

    set_centers();
    return true;
}

uint32_t Orbit::Do()
{
    for (light_count_t i = 0; i < count_; ++i)
    {
        Orbiter *o = &orbiter_[i];
        o->Do();
        light_count_t x = o->x_local(light_count_, orbiter_center_[i]);

        if (should_erase_ && last_x_[i] != x)
        {
            g35_.set_color(last_x_[i], 255, COLOR_BLACK);
            last_x_[i] = x;
        }
        g35_.set_color(x, 255, o->color());
    }
    return delay_;
}

Orbit::Orbit(G35& g35, bool should_erase)
  : LightProgram(g35),
    should_erase_(should_erase),
    count_(MAX_OBJECTS),
    light_count_(g35_.get_light_count())
{
    delay_default_ = g35_.get_bulb_frame() >> 1;
}

void Orbit::set_centers()
{
    for (light_count_t i = 0; i < count_; ++i)
    {
        orbiter_center_[i] = rand() % light_count_;
        last_x_[i] = 0;
    }
}

OrbitSmudge::OrbitSmudge(G35& g35)
  : Orbit(g35, false)
{
    DebugPrintf("OrbitSmudge\n");
}

#pragma once

#include "pebble.h"

void show_analog(Window* window);
void hide_analog(void);

#define NUM_CLOCK_TICKS 11

static const GPathInfo MINUTE_HAND_POINTS = {
  4, (GPoint []) {
    { -5, 5 },
    { 5, 5 },
    { 2, -60 },
    { -2, -60 }
  }
};

static const GPathInfo HOUR_HAND_POINTS = {
  4, (GPoint []) {
    {-4, 10},
    {4, 10},
    {2, -40},
    {-2, -40}
  }
};
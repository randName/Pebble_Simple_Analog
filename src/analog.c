#include <pebble.h>
#include "analog.h"

static GPath *minute_arrow;
static GPath *hour_arrow;
static Layer *hands_layer;

static void hands_update_proc(Layer *layer, GContext *ctx) {
  time_t now = time(NULL);
  struct tm *t = localtime(&now);

  // minute/hour hand
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_context_set_stroke_color(ctx, GColorBlack);

  gpath_rotate_to(minute_arrow, TRIG_MAX_ANGLE * t->tm_min / 60);
  gpath_draw_filled(ctx, minute_arrow);
  gpath_draw_outline(ctx, minute_arrow);

  gpath_rotate_to(hour_arrow, (TRIG_MAX_ANGLE*(((t->tm_hour%12)*6)+(t->tm_min/10)))/(12*6));
  gpath_draw_filled(ctx, hour_arrow);
  gpath_draw_outline(ctx, hour_arrow);
}

void show_analog(Window* window) {
  // init hand paths
  minute_arrow = gpath_create(&MINUTE_HAND_POINTS);
  hour_arrow = gpath_create(&HOUR_HAND_POINTS);

  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  const GPoint center = grect_center_point(&bounds);

  gpath_move_to(minute_arrow, center);
  gpath_move_to(hour_arrow, center);
  
  hands_layer = layer_create(bounds);
  layer_set_update_proc(hands_layer, hands_update_proc);
  layer_add_child(window_layer, hands_layer);
}

void hide_analog(void) {
  layer_destroy(hands_layer);
  gpath_destroy(minute_arrow);
  gpath_destroy(hour_arrow);
}
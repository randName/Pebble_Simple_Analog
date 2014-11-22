#include <pebble.h>
  
//#include "layout.h"
#include "analog.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_14;
static TextLayer *date;
static Layer *bluetooth;
static Layer *battery;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, true);
  
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  // date
  date = text_layer_create(GRect(20, 150, 100, 20));
  text_layer_set_background_color(date, GColorClear);
  text_layer_set_text_color(date, GColorWhite);
  text_layer_set_text(date, "Mon  1 Jan 2014");
  text_layer_set_text_alignment(date, GTextAlignmentCenter);
  text_layer_set_font(date, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)date);
  
  // bluetooth
  bluetooth = layer_create(GRect(0, 0, 15, 15));
  layer_add_child(window_get_root_layer(s_window), (Layer *)bluetooth);
  
  // battery
  battery = layer_create(GRect(129, 0, 15, 15));
  layer_add_child(window_get_root_layer(s_window), (Layer *)battery);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(date);
  layer_destroy(bluetooth);
  layer_destroy(battery);
}
// END AUTO-GENERATED UI CODE

static GPath *bluez;
static const GPathInfo BLUETOOTH_POINTS = {
  6, (GPoint []) { { 2, 4 }, { 12, 10 }, { 7, 13 }, { 7, 1 }, { 12, 4 }, { 2, 10 } }
};

static void bluetooth_update_proc(Layer *layer, GContext *ctx) {
  graphics_context_set_stroke_color(ctx, bluetooth_connection_service_peek() ? GColorWhite : GColorBlack);
  gpath_draw_outline(ctx, bluez);
}

static void battery_update_proc(Layer *layer, GContext *ctx) {
  static BatteryChargeState c_state;
  c_state = battery_state_service_peek();
  
  graphics_context_set_stroke_color(ctx, c_state.is_charging ? GColorWhite : GColorBlack);
  graphics_draw_rect(ctx, GRect(0,0,15,15));
  
  graphics_context_set_stroke_color(ctx, GColorWhite);
  graphics_context_set_fill_color(ctx, GColorWhite);

  switch(c_state.charge_percent/10){
    case 10: graphics_fill_rect(ctx, GRect(1,1,13,13), 0, GCornerNone); break;
    case 9: graphics_draw_rect(ctx, GRect(2,10,3,3));
    case 8: graphics_draw_rect(ctx, GRect(6,10,3,3));
    case 7: graphics_draw_rect(ctx, GRect(2,6,3,3));
    case 6: graphics_draw_rect(ctx, GRect(10,10,3,3));
    case 5: graphics_draw_rect(ctx, GRect(2,2,3,3));
    case 4: graphics_draw_rect(ctx, GRect(6,6,3,3));
    case 3: graphics_draw_rect(ctx, GRect(10,6,3,3));
    case 2: graphics_draw_rect(ctx, GRect(6,2,3,3));
    case 1: graphics_draw_rect(ctx, GRect(10,2,3,3));
  }
}

static void handle_window_load(Window* window) {
  show_analog(s_window);
  bluez = gpath_create(&BLUETOOTH_POINTS);
  layer_set_update_proc(bluetooth, bluetooth_update_proc);
  layer_set_update_proc(battery, battery_update_proc);
}

static void handle_window_unload(Window* window) {
  destroy_ui();
  hide_analog();
}

static void show_layout(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = handle_window_load,
    .unload = handle_window_unload
  });
  window_stack_push(s_window, true);
}

static void hide_layout(void) {
  window_stack_remove(s_window, true);
}
#include <pebble.h>
  
#include "layout.c"

static void handle_battery(BatteryChargeState c_state) {
  layer_mark_dirty(battery);
}
  
static void handle_bluetooth(bool connected) {
  layer_mark_dirty(bluetooth);
}
  
static void handle_tick(struct tm *tick_time, TimeUnits units_changed) {
  layer_mark_dirty(window_get_root_layer(s_window));

  static char date_buf[] = "Mon  1 Jan 2014";
  
  strftime(date_buf, sizeof("Mon  1 Jan 2014"), "%a %e %b %Y", tick_time);
  text_layer_set_text(date, date_buf);
  
  handle_battery(battery_state_service_peek());
}

void init(void) {
  show_layout();
  tick_timer_service_subscribe(MINUTE_UNIT, handle_tick);
  battery_state_service_subscribe(&handle_battery);
  bluetooth_connection_service_subscribe(&handle_bluetooth);
}

void deinit(void) {
  hide_layout();
  tick_timer_service_unsubscribe();
  battery_state_service_unsubscribe();
  bluetooth_connection_service_unsubscribe();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
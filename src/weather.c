#include "coordinate.h"
#include "weather.h"
#include <stdlib.h>

struct weather global_weather;

void create_weather() {
  global_weather.wind = rand() % 6;
  global_weather.wind_speed = (rand() % 10) + (rand() % 10);
  if ((rand() & 7) == 0) {
    global_weather.kind = rand() % 4;
  } else {
    global_weather.kind = Clear;
  }
  altitude_t alt;
  unsigned x = rand() % 100;
  if (x < 50) {
    alt = 6000 + (rand() % 6000);
  } else if (x < 70) {
    alt = 10000 + (rand() % 2000);
  } else if (x < 80) {
    alt = 3000 + (rand() % 3000);
  } else if (x < 90) {
    alt = 12000 + (rand() % 3000);
  } else {
    alt = 15000 + (rand() % 5000);
  }
  global_weather.cloud_base = alt;
  global_weather.cloud_top = alt + 300 + rand() % 3000;
  if (global_weather.cloud_top - global_weather.cloud_base > 600) {
    global_weather.cloud_intensity = umin(100, 60 + rand() % 60);
  } else {
    global_weather.cloud_intensity = rand() % 40 + rand() % 30;
  }
}

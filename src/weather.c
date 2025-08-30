#include "coordinate.h"
#include "playstate.h"
#include "random.h"
#include "weather.h"
#include <stdlib.h>

struct weather global_weather;

static void set_wind_direction(uint16_t nw, uint16_t sw) {
  uint16_t random = random_u16();
  if (random < nw) {
    global_weather.wind = NorthWest;
  } else if (random < sw) {
    global_weather.wind = SouthWest;
  } else {
    global_weather.wind = NorthEast;
  }
}

static void set_wind_speed(uint16_t nope, uint16_t medium) {
  uint16_t random = random_u16();
  if (random < nope) {
    global_weather.wind_speed = 0;
  } else if (random < medium) {
    global_weather.wind_speed = 8; // half hex
  } else {
    global_weather.wind_speed = 16;  // full hex
  }
}

struct define_altitude_band {
  uint16_t limit;
  enum altitude_band lo;
  enum altitude_band hi;
};

static void set_cloud_base(struct define_altitude_band *defs) {
  uint16_t random = random_u16();
  while (1) {
    global_weather.cloud_base = defs->lo;
    global_weather.cloud_top = defs->hi;
    if (defs->limit < random || defs->limit == 0) {
      break;
    }
    defs++;
  }
}

static void set_weather_kind(uint16_t clear, uint16_t mostly_sunny,
                             uint16_t cloudy, uint16_t rainy,
                             uint16_t foggy) {
  uint16_t random = random_u16();
  if (random < clear) {
    global_weather.kind = Clear;
    global_weather.cloud_intensity = 0;
  } else if (random < mostly_sunny) {
    global_weather.kind = MostlySunny;
    struct define_altitude_band table[] = {
      { 65536ul * 2 / 10, Low, Low },
      { 65536ul * 6 / 10, Low, Medium },
      { 65536ul * 8 / 10, Medium, High },
      { 0, High, VeryHigh }
    };
    set_cloud_base(table);
    global_weather.cloud_intensity = umin(100, rand() % 30);
  } else if (random < cloudy) {
    global_weather.kind = Cloudy;
    struct define_altitude_band table[] = {
      { 65536ul * 6 / 10, Low, Low },
      { 65536ul * 8 / 10, Medium, Medium },
      { 65536ul * 9 / 10, High, High },
      { 0, VeryHigh, VeryHigh }
    };
    set_cloud_base(table);
    global_weather.cloud_intensity = umin(100, 30 + rand() % 50);
  } else if (random < rainy) {
    global_weather.kind = Rain;
    struct define_altitude_band table[] = {
      { 65536ul * 7 / 10, Low, Low },
      { 0, Medium, Medium },
    };
    set_cloud_base(table);
    global_weather.cloud_intensity = umin(100, 70 + rand() % 30);
  } else if (random <= foggy) {
    global_weather.kind = Fog;
    struct define_altitude_band table[] = {
      { 65536ul * 7 / 10, Deck, Deck },
      { 0, Low, Low },
    };
    set_cloud_base(table);
    global_weather.cloud_intensity = umin(100, 80 + rand() % 30);
  } else {
    global_weather.kind = Snow;
    struct define_altitude_band table[] = {
      { 65536ul * 7 / 10, Low, Low },
      { 0, Medium, Medium },
    };
    set_cloud_base(table);
    global_weather.cloud_intensity = umin(100, 70 + rand() % 30);
  }
}

void create_weather(struct playstate *playstate) {
  uint16_t nw, sw;
  switch (playstate->current_time.tm_mon) {
  case 2:   // march
    set_wind_direction(65536ul * 4 / 10, 65536ul * 9 / 10);
    set_wind_speed(65536ul * 4 / 10, 65536ul * 8 / 10);
    set_weather_kind(65536ul * 2 / 10, 65536ul * 4 / 10, 65536ul * 5 / 10,
                     65536ul * 8 / 10, 65536ul * 9 / 10);
    break;
  case 3:   // april
    set_wind_direction(65536ul * 5 / 10, 65536ul * 9 / 10);
    set_wind_speed(65536ul * 5 / 10, 65536ul * 9 / 10);
    set_weather_kind(65536ul * 2 / 10, 65536ul * 4 / 10, 65536ul * 6 / 10,
                     65536ul * 8 / 10, 65536ul * 9 / 10);
    break;
  default:  // may
    set_wind_direction(65536ul * 3 / 10, 65536ul * 7 / 10);
    set_wind_speed(65536ul * 6 / 10, 65536ul * 9 / 10);
    set_weather_kind(65536ul * 4 / 10, 65536ul * 5 / 10, 65536ul * 7 / 10,
                     65536ul * 9 / 10, ~0);
    break;
  }
  if (global_weather.kind == Fog && playstate->current_time.tm_hour >= 10) {
    global_weather.kind = MostlySunny;
  }

}

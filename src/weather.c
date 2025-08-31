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
  }
  else if (random < sw) {
    global_weather.wind = SouthWest;
  }
  else {
    global_weather.wind = NorthEast;
  }
}

static void set_wind_speed(uint16_t nope, uint16_t medium) {
  uint16_t random = random_u16();
  if (random < nope) {
    global_weather.wind_speed = 0;
  }
  else if (random < medium) {
    global_weather.wind_speed = 8; // half hex
  }
  else {
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

static void weather_is_clear() {
  global_weather.kind = Clear;
  global_weather.cloud_intensity = 0;
}

static void weather_is_mostly_sunny() {
  global_weather.kind = MostlySunny;
  struct define_altitude_band table[] = {
    { D10_RANGE(2), Low, Low },
    { D10_RANGE(6), Low, Medium },
    { D10_RANGE(8), Medium, High },
    { 0, High, VeryHigh }
  };
  set_cloud_base(table);
  global_weather.cloud_intensity = umin(100, rand() % 30);
}

static void weather_is_cloudy() {
  global_weather.kind = Cloudy;
  struct define_altitude_band table[] = {
    { D10_RANGE(6), Low, Low },
    { D10_RANGE(8), Medium, Medium },
    { D10_RANGE(9), High, High },
    { 0, VeryHigh, VeryHigh }
  };
  set_cloud_base(table);
  global_weather.cloud_intensity = umin(100, 30 + rand() % 50);
}

static void weather_is_rain() {
  global_weather.kind = Rain;
  struct define_altitude_band table[] = {
    { D10_RANGE(7), Low, Low },
    { 0, Medium, Medium },
  };
  set_cloud_base(table);
  global_weather.cloud_intensity = umin(100, 70 + rand() % 30);
}

static void weather_is_fog() {
  global_weather.kind = Fog;
  struct define_altitude_band table[] = {
    { D10_RANGE(7), Deck, Deck },
    { 0, Low, Low },
  };
  set_cloud_base(table);
  global_weather.cloud_intensity = umin(100, 80 + rand() % 30);
}

static void weather_is_snow() {
  global_weather.kind = Snow;
  struct define_altitude_band table[] = {
    { D10_RANGE(7), Low, Low },
    { 0, Medium, Medium },
  };
  set_cloud_base(table);
  global_weather.cloud_intensity = umin(100, 70 + rand() % 30);
}

static void set_kind(enum weather_kind kind) {
  typedef void (*set_clouds)(void);
  static set_clouds table[] = {
    weather_is_clear, weather_is_mostly_sunny, weather_is_cloudy,
    weather_is_rain, weather_is_fog, weather_is_snow
  };
  table[kind]();
}

static void set_weather_kind(uint16_t clear, uint16_t mostly_sunny,
                             uint16_t cloudy, uint16_t rainy,
                             uint16_t foggy) {
  uint16_t random = random_u16();
  if (random < clear) {
    weather_is_clear();
  }
  else if (random < mostly_sunny) {
    weather_is_mostly_sunny();
  }
  else if (random < cloudy) {
    weather_is_cloudy();
  }
  else if (random < rainy) {
    weather_is_rain();
  }
  else if (random <= foggy) {
    weather_is_fog();
  }
  else {
    weather_is_snow();
  }
}

void create_weather(struct playstate *playstate) {
  uint16_t nw, sw;
  switch (playstate->current_time.tm_mon) {
  case 2:   // march
    set_wind_direction(D10_RANGE(4), D10_RANGE(9));
    set_wind_speed(D10_RANGE(4), D10_RANGE(8));
    set_weather_kind(D10_RANGE(2), D10_RANGE(4), D10_RANGE(5),
                     D10_RANGE(8), D10_RANGE(9));
    break;
  case 3:   // april
    set_wind_direction(D10_RANGE(5), D10_RANGE(9));
    set_wind_speed(D10_RANGE(5), D10_RANGE(9));
    set_weather_kind(D10_RANGE(2), D10_RANGE(4), D10_RANGE(6),
                     D10_RANGE(8), D10_RANGE(9));
    break;
  default:  // may
    set_wind_direction(D10_RANGE(3), D10_RANGE(7));
    set_wind_speed(D10_RANGE(6), D10_RANGE(9));
    set_weather_kind(D10_RANGE(4), D10_RANGE(5), D10_RANGE(7),
                     D10_RANGE(9), ~0);
    break;
  }
  if (global_weather.kind == Fog && playstate->current_time.tm_hour >= 10) {
    weather_is_cloudy();
  }
}

void weather_phase(struct playstate *playstate) {
  if (playstate->turn && (playstate->turn & 7) == 0) {
    switch (roll2d10()) {
    case 2:       // strong wind
      global_weather.wind_speed = 32;   // 2 hexes worth of wind
      break;
    case 3:       // gusts of wind
    case 4:
      global_weather.wind_speed = 24;   // 1.5 hexes worth of wind
      break;
    case 5:       // wind direction changes
    case 6:
    case 7:
    case 8: {
      uint16_t random = random_u16();
      if (random < D10_RANGE(4)) {
        global_weather.wind = NorthWest;
      }
      else if (random < D10_RANGE(8)) {
        global_weather.wind = SouthWest;
      }
      else {
        global_weather.wind = NorthEast;
      }
      break;
    }
    case 9:       // weather improves
    case 10:
    case 11:
    case 12: {
      enum weather_kind kind = global_weather.kind;
      if (kind > Clear) {
        kind--;
      }
      if (kind == Fog && playstate->current_time.tm_hour >= 10) {
        kind = Rain;
      }
      set_kind(global_weather.kind);
      break;
    }
    case 13:      // weather gets worse
    case 14:
    case 15:
    case 16: {
      enum weather_kind kind = global_weather.kind;
      if (kind != Snow) {
        kind++;
      }
      if (kind == Fog && playstate->current_time.tm_hour >= 10) {
        kind = Snow;
      }
      if (kind == Snow && playstate->current_time.tm_mon > 3) {
        // no snow in May
        kind = Rain;
      }
      set_kind(global_weather.kind);
      break;
    }
    case 17:      // gusts of wind
      global_weather.wind_speed = 16;   // 1 hex worth of wind
      break;
    case 18:      // gusts of wind
    case 19:
      global_weather.wind_speed = 16;   // 0.5 hex worth of wind
      break;
    case 20:      // calm
      global_weather.wind_speed = 0;   // no wind
      break;



    }
  }
}

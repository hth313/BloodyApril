#ifndef __WEATHER_H__
#define __WEATHER_H__

#include "altitude.h"
#include "distance.h"
#include "map.h"
#include "playstate.h"

typedef enum weather_kind {
  Clear, MostlySunny, Cloudy, Rain, Snow, Fog
} weather_kind;

struct weather {
  direction wind;
  distance_t wind_speed;   // 1/16 hex fraction speed, see distance.h
  weather_kind kind;
  altitude_t cloud_base;
  altitude_t cloud_top;
  unsigned cloud_intensity;     // 0-100 for thickness of cloud
};

extern struct weather global_weather;

extern void create_weather(struct playstate *playstate);

#endif // __WEATHER_H__

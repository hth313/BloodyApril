#ifndef __WEATHER_H__
#define __WEATHER_H__

#include "altitude.h"
#include "map.h"

typedef enum weather_kind {
  Clear, Fog, Rain, Snow
} weather_kind;

struct weather {
  direction wind;
  unsigned wind_speed;
  weather_kind kind;
  altitude_t cloud_base;
  altitude_t clout_top;
  unsigned cloud_intensity;     // 0-100 for thickness of cloud
};

extern struct weather global_weather;

extern void create_weather();

#endif // __WEATHER_H__

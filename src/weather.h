#ifndef __WEATHER_H__
#define __WEATHER_H__

#include "altitude.h"
#include "map.h"

typedef enum weather_kind {
  Clear, Fog, Rain, Snow
} weather_kind;

typedef struct weather {
  direction wind;
  unsigned wind_speed;
  weather_kind kind;
  altitude cloud_level;
  unsigned intensity;     // 0-100 for thickness of cloud
} weather;

#endif // __WEATHER_H__

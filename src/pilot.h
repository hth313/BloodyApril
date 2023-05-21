#ifndef __PILOT_H__
#define __PILOT_H__

#include "unit.h"

struct pilot {
  char const *name;
  enum unit_id unit;
  unsigned strength;
  unsigned duration;
  unsigned kills;
};

// We have an array of airplane data we can look up in.
extern const struct pilot *pilot_data[];

#endif // __PILOT_H__

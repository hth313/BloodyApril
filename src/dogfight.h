#ifndef __DOGFIGHT_H__
#define __DOGFIGHT_H__

#include <stdbool.h>
#include "airplane.h"

#define MAX_AIRPLANE_IN_DOGFIGHT 8

struct dogfight {
  airplane *plane[2][MAX_AIRPLANE_IN_DOGFIGHT];
  bool side0_attacker;
};

#endif // __DOGFIGHT_H__

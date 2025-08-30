#ifndef __DISTANCE_H__
#define __DISTANCE_H__

#include <stdint.h>

// Distance is in number of hexes, scaled by 16 to allow for simple
// fraction. It is used for speed and movement short distance.
typedef unsigned distance_t;

inline distance_t scale_distance_to_hex(distance_t distance) {
  return (distance + 8) >> 4;
}

#endif // __DISTANCE_H__

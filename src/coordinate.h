#ifndef __COORDINATE_H__
#define __COORDINATE_H__

#include <stdbool.h>
#include <stdint.h>

typedef enum direction {
  NortWest, West, SouthWest, SouthEast, East, NorthEast
} direction;

// Use axial coordinates, which are cube coordinates storing two of the
// three dimensions. The size may be somewhat limited here at the moment
// with signed 8, but in practise it is a lot of hexes.
typedef union coordinate {
  struct {
    int8_t q, r;
  };
  uint16_t qr;
} coordinate;

// Describes the actual location, which can be a single coordinate (both same),
// it two adjacent hexes in which case we are located on the border;
typedef struct location {
  coordinate main;
  coordinate secondary;
} location;

// Tells whether the location describes a single hex. If false it describes
// a location that is the border between two hexes.
inline bool on_hex(location loc) {
  return loc.main.qr == loc.secondary.qr;
}

inline bool abs8(int8_t a) {
  if (a >= 0)
    return a;
  else
    return -a;
}

inline unsigned umax(unsigned a, unsigned b) {
  if (a < b) {
    return b;
  } else {
    return a;
  }
}

inline unsigned umin(unsigned a, unsigned b) {
  if (a < b) {
    return a;
  } else {
    return b;
  }
}

#endif //  __COORDINATE_H__

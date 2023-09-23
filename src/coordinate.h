#ifndef __COORDINATE_H__
#define __COORDINATE_H__

#include <stdbool.h>
#include <stdint.h>

// Hex directions.
typedef enum hex_direction {
  NortWest, West, SouthWest, SouthEast, East, NorthEast
} direction;

// Clock direction (this is what flight do, 0-11.
typedef uint_fast8_t clock_direction;

typedef enum turn { Left, Right } turn;

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

// X,Y coordinates start at 0,0 in upper left corner.
// An actor hex location is 32x32 pixels, which is made up by four 16x16 tiles.
// We lay out hexes as such:
//
// OOBB              row 0
// OOBB              row 0
//  DDXX             row 1
//  DDXX             row 1
//
// Note that odd rows are shifted 16 pixes right compared to even rows.
//
// OO   is  q,r ->  0,0   (row 0)
// OO
//
// BB   is  q,r ->  1,0   (row 0)
// BB
//
// DD   is q,r  ->  0,1   (row 1)
// DD
//
// Reference: https://www.redblobgames.com/grids/hexagons/#coordinates

// Coordinate to pixel positions
inline uint16_t pixel_x(coordinate c) {
  return c.q * 32 + (c.r & 1) * 16;
}

inline uint16_t pixel_y(coordinate c) {
  return c.r * 32;
}

// Location to pixel position
inline uint16_t loc_pixel_x(location loc) {
  return (pixel_x(loc.main) + pixel_x(loc.secondary)) >> 1;
}

inline uint16_t loc_pixel_y(location loc) {
  return (pixel_y(loc.main) + pixel_y(loc.secondary)) >> 1;
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

// **********************************************************************

inline location coordinate_to_location(coordinate pos) {
  return (location) { .main = pos, .secondary = pos };
}

extern location move(location loc, clock_direction heading);

#endif //  __COORDINATE_H__

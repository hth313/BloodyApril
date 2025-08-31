#ifndef __COORDINATE_H__
#define __COORDINATE_H__

#include <stdbool.h>
#include <stdint.h>

// Directions. 0 being north going clockwise.
// Airplane movements are in 30 degree increments as they can be on the border
// between two hexes.
// Ground units follow 60 degree increments staying inside hexes.
// We implement this using a value 0-11 stored inside a suitable small integer.
typedef int_fast8_t direction;

#define NorthWest 10
#define SouthWest  8
#define NorthEast  2

typedef enum turn { Left, Right } turn;

// Use axial coordinates, which are cube coordinates storing two of the
// three dimensions. The size may be somewhat limited here at the moment
// with signed 8, but in practise it is a lot of hexes.
typedef union coordinate {
  struct {
  uint16_t qr;
#ifdef __BIG_ENDIAN__
    int8_t q, r;
#else
    int8_t r, q;
#endif
  };
} coordinate;

// This is used to mark the end of list/arrays or as a coordinate that is
// not on the map.
#define CoordinateEndMarker 0xffff

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

inline uint8_t abs8(int8_t a) {
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

extern coordinate direction_vector[6];

inline location coordinate_to_location(coordinate pos) {
  return (location) { .main = pos, .secondary = pos };
}

extern location move(location loc, direction heading);

// Find the coordinate neighbor of a hex.
inline coordinate neighbor(coordinate coord, direction direction) {
  return (coordinate) { .qr = direction_vector[direction].qr + coord.qr };
}

inline uint_fast8_t distance(coordinate a, coordinate b) {
  coordinate vec = (coordinate) { .qr = a.qr - b.qr };
  return (abs8(vec.q) + abs8(vec.q + vec.r) + abs8(vec.r)) / 2;
}

inline bool location_equal(location *loc1, location *loc2) {
  return loc1->main.qr == loc2->main.qr && loc1->secondary.qr == loc2->secondary.qr;
}

inline direction normalize_direction(direction heading) {
  if (heading < 0) heading += 12;
  if (heading > 11) heading -= 12;
  return heading;
}

#endif //  __COORDINATE_H__

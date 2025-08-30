#include "coordinate.h"
#include <stdint.h>

extern bool on_hex(location loc);
extern uint16_t pixel_x(coordinate c);
extern uint16_t pixel_y(coordinate c);
extern uint16_t loc_pixel_x(location loc);
extern uint16_t loc_pixel_y(location loc);
extern uint8_t abs8(int8_t a);
extern unsigned umax(unsigned a, unsigned b);
extern unsigned umin(unsigned a, unsigned b);
extern location coordinate_to_location(coordinate pos);
extern coordinate neighbor(coordinate coord, direction direction);

inline uint_fast8_t distance(coordinate a, coordinate b);

// Move a flight in given direction
location move(location loc, direction heading) {
  switch (heading) {
  case 0:
    if (loc.main.qr == loc.secondary.qr) {
      loc.main.r--;
      loc.secondary.q++;
      loc.secondary.r--;
    } else {
      loc.secondary.r--;
      loc.main = loc.secondary;
    }
    break;
  case 1:
    loc.main.q++;
    loc.main.r--;
    loc.secondary = loc.main;
    break;
  case 2:
    if (loc.main.qr == loc.secondary.qr) {
      loc.main.q++;
      loc.main.r--;
      loc.secondary.q++;
    } else {
      loc.main.q++;
      loc.secondary = loc.main;
    }
    break;
  case 3:
    loc.main.q++;
    loc.secondary = loc.main;
    break;
  case 4:
    if (loc.main.qr == loc.secondary.qr) {
      loc.main.q++;
      loc.secondary.r++;
    } else {
      loc.main.r++;
      loc.secondary = loc.main;
    }
    break;
  case 5:
    loc.main.r++;
    loc.secondary = loc.main;
    break;
  case 6:
    if (loc.main.qr == loc.secondary.qr) {
      loc.main.r++;
      loc.secondary.q--;
      loc.secondary.r++;
    } else {
      loc.secondary.r++;
      loc.main = loc.secondary;
    }
    break;
  case 7:
    loc.main.q--;
    loc.main.r++;
    loc.secondary = loc.main;
    break;
  case 8:
    if (loc.main.qr == loc.secondary.qr) {
      loc.main.q--;
      loc.main.r++;
      loc.secondary.q--;
    } else {
      loc.main.q--;
      loc.secondary = loc.main;
    }
    break;
  case 9:
    loc.main.q--;
    loc.secondary = loc.main;
    break;
  case 10:
    if (loc.main.qr == loc.secondary.qr) {
      loc.main.q--;
      loc.secondary.r--;
    } else {
      loc.main.r--;
      loc.secondary = loc.main;
    }
    break;
  case 11:
    loc.main.r--;
    loc.secondary = loc.main;
    break;
  }
  return loc;
}

coordinate direction_vector[6] = {
    {0x01ff}, // NorthEast  q +1, r -1
    {0x0100}, // East       q +1, r  0
    {0x0001}, // SouthEast  q  0, r +1
    {0xff01}, // SouthWest  q -1, r +1
    {0xff00}, // West       q -1, r  0
    {0x00ff}, // NorthWest  q  0, r -1
};

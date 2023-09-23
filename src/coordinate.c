#include "coordinate.h"

extern bool on_hex(location loc);
extern uint16_t pixel_x(coordinate c);
extern uint16_t pixel_y(coordinate c);
extern uint16_t loc_pixel_x(location loc);
extern uint16_t loc_pixel_y(location loc);
extern bool abs8(int8_t a);
extern unsigned umax(unsigned a, unsigned b);
extern unsigned umin(unsigned a, unsigned b);
extern location coordinate_to_location(coordinate pos);

// Move a flight in given direction
location move(location loc, clock_direction heading) {
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

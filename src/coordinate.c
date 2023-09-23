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

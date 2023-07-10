#ifndef __FLIGHT_H__
#define __FLIGHT_H__

#include "list.h"

// A flight is a group of airplanes flying together. It may suffice to show one
// airplane (the top one) with some indicator that there are more.
// All airplanes in a flight is seen as a single unit with the same
// location and heading. Individual airplanes in a flight may exist at different
// altitudes, especially during combat situations.
typedef struct flight {
  struct typed_node;     // Part of a linked list for its hex location
  struct list airplanes; // Airplanes in this flight
  location position;
  direction heading;
  uint16_t move_order;
#define MOVE_ORDER_LEVEL          0x0000
#define MOVE_ORDER_CLIMB          0x0001
#define MOVE_ORDER_DECEND         0x0002
#define MOVE_ORDER_SPIN_OUT       0x0004
#define MOVE_ORDER_TURN_LEFT      0x0008
#define MOVE_ORDER_TURN_RIGHT     0x0010
} flight;

// **********************************************************************

extern flight *new_flight(location *position, direction heading);
extern void drop_flight(flight *p);

#endif // __FLIGHT_H__

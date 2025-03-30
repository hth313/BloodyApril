#ifndef __FLIGHT_H__
#define __FLIGHT_H__

#include <stdbool.h>
#include "altitude.h"
#include "coordinate.h"
#include "list.h"
#include "actor_visual.h"

struct playstate;

enum detection {
    Undetected, Detected, VisuallySighted,
    DetectedPreviouslyVisuallySighted
};

// A flight is a group of airplanes flying together. It may suffice to show one
// airplane (the top one) with some indicator that there are more.
// All airplanes in a flight is seen as a single unit with the same
// location and heading. Individual airplanes in a flight may exist at different
// altitudes, especially during combat situations.
struct flight {
  // When on the ground part of a list owned by an aerodrome.
  // When airborne, it is owned by a list in playstate, this in part because
  // flights move frequently, but also that they may be placed between hexes.
  // When engaged in a dogfight, owned by the xx_powers list of the dogfight.
  struct typed_node node;
  struct list airplanes;   // Airplanes in this flight
  struct actor_visual visual;
  location loc;
  int16_t fraction;        // tenths of a hex movement kept or borrowed
  altitude_t desired_altitude;
  clock_direction heading;
  uint8_t free_turn;
  uint8_t max_turn;
  bool movement_marked;   // set when scattered out of combat, costs one MP to remove
  bool allied;
  uint16_t move_order;
#define MOVE_ORDER_LEVEL          0x0000
#define MOVE_ORDER_CLIMB          0x0001
#define MOVE_ORDER_DECEND         0x0002
#define MOVE_ORDER_SPIN_OUT       0x0004
#define MOVE_ORDER_TURN_LEFT      0x0008
#define MOVE_ORDER_TURN_RIGHT 0x0010
  enum detection detection;
  bool drawn;
};

// **********************************************************************

extern struct flight *new_flight(location position, direction heading,
				 actor_tile_t *actor_tile);
extern void drop_flight(struct playstate *ps, struct flight *p);
extern bool prune_downed(struct playstate *ps, struct flight *flight);

#endif // __FLIGHT_H__

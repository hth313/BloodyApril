#ifndef __FLIGHT_H__
#define __FLIGHT_H__

#include <stdbool.h>
#include "altitude.h"
#include "coordinate.h"
#include "distance.h"
#include "list.h"
#include "actor_visual.h"

struct playstate;

enum detection {
    Undetected, Detected, VisuallySighted,
    DetectedPreviouslyVisuallySighted
};

enum move_order_tag {
  Landed, MaintainLevel, ToAltitude, SpinOut, TurnLeft, TurnRight
};

union move_order {
  enum move_order_tag tag;

  struct target_heading {
    enum move_order_tag tag;
    direction heading;
  } order_heading;

  struct target_altitude {
    enum move_order_tag tag;
    altitude_t altitude;
  } order_altitude;
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
  distance_t fraction;        // tenths of a hex movement kept or borrowed
  altitude_t desired_altitude;
  direction heading;
  uint8_t free_turn;
  uint8_t max_turn;
  bool movement_marked;   // set when scattered out of combat, costs one MP to remove
  bool allied;
  union move_order move_order;
  enum detection detection;
};

// **********************************************************************

extern struct flight *new_flight(bool allied, location position, direction heading,
				 struct airplane *airplanes[]);
extern void drop_flight(struct playstate *ps, struct flight *p);
extern bool prune_downed(struct playstate *ps, struct flight *flight);
extern void wind_drift(struct playstate *ps);

inline struct flight *new_allied_flight(location position, direction heading,
                                        struct airplane *airplanes[]) {
  return new_flight(true, position, heading, airplanes);
}

inline struct flight *new_centrl_flight(location position, direction heading,
                                        struct airplane *airplanes[]) {
  return new_flight(false, position, heading, airplanes);
}

inline struct airplane *head_airplane(struct flight *flight) {
  if (!empty_list(&flight->airplanes)) {
    struct airplane *airplane = (struct airplane*)(flight->airplanes.head);
    return airplane;
  }
  else {
    return 0;
  }
}

#endif // __FLIGHT_H__

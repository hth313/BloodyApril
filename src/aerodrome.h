#ifndef __AERODROME_H__
#define __AERODROME_H__

#include "coordinate.h"
#include "list.h"
#include "actor_visual.h"

// An aerodrome is a place where airplanes are stored, takes off from
// and can land at. They have a fixed location and identity in the map
// when they are active.
// Airplanes on the ground are either kept in a flights (group of airplanes)
// plus a flat list of airplanes that may be added to a flight.
struct aerodrome {
  struct node node;     // Belongs to a list of existing aerodromes in playstate
  struct actor_visual visual;
  const char *name;           // Name of the aerodrome
  coordinate pos;             // The sector of this aerodrome
  bool allied;                // Set if this aerodrom belongs to the allied side.
  struct list flights;        // All the flights parked here.
  struct list airplanes;      // Airplanes on the ground not currently part of a flight
  struct list squadron;       // The squadrons stationed at this aerodrome
};

// **********************************************************************

extern void create_aerodromes(struct playstate *playstate);

#endif // __AERODROME_H__

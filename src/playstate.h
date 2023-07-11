#ifndef __PLAYSTATE_H__
#define __PLAYSTATE_H__

#include <time.h>
#include "actor.h"
#include "scenario.h"

// The playstate keeps track of the map, the game actors, the scenario, time, play
// turn count etc.
struct playstate {
  struct list flights;            // Active flights in the air
  actorsmap actors;               // Other actors, such as ground unites or ballons
  struct list aerodromes;         // List of all aerodromes
  struct scenario *scenario;      // The active scenario, or NULL
  struct list accomplished;       // List of accomplished objectives, or state objects
                                  // related to it (partial accomplishments)
  unsigned turn;                  // Number of turns played
  struct playfield *playfield;    // Information about the playfield (map) being played.
  struct tm current_time;
  struct list downed_allied;      // Downed allied airplanes
  struct list downed_central;     // Downed central powers airplanes
};

#endif // __PLAYSTATE_H__

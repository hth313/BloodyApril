#ifndef __PLAYSTATE_H__
#define __PLAYSTATE_H__

#include <time.h>
#include "actor.h"
#include "aerodrome.h"
#include "playfield.h"
#include "scenario.h"
#include "timeofday.h"

// The playstate keeps track of the map, the game actors, the scenario, time, play
// turn count etc.
struct playstate {
  struct list flights;            // Active flights in the air
  actorsmap actors;               // Other actors, such as ground unites or ballons
  struct aerodrome *aerodromes;   // List of all aerodromes
  struct scenario *scenario;      // The active scenario, or NULL
  struct list *accomplished;      // List of accomplished objectives, or state objects
                                  // related to it (partial accomplishments)
  unsigned turn;                  // Number of turns played
  struct playfield *playfield;    // Information about the playfield (map) being played.
  struct tm current_time;


};

#endif // __PLAYSTATE_H__

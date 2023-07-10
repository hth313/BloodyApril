#ifndef __PLAYSTATE_H__
#define __PLAYSTATE_H__

#include "actors.h"
#include "aerodrome.h"
#include "playfield.h"
#include "scenario.h"
#include "timeofday.h"

// The playstate keeps track of the map, the game actors, the scenario, time, play
// turn count etc.
struct playstate {
  struct list flights;            // Active flights in the air
  all_actors actors;              // Other actors, such as ground unites or ballons
  struct aerodrome *aerodromes;   // List of all aerodromes
  struct scenario *scenario;      // The active scenario, or NULL
  struct list *accomplished;      // List of accomplished objectives, or state objects
                                  // related to it (partial accomplishments)
  unsigned turn;                  // Number of turns played
  struct playfield *playfield;    // Information about the playfield (map) being played.
  struct time_of_day time_of_day;


};

#endif // __PLAYSTATE_H__

#ifndef __PLAYSTATE_H__
#define __PLAYSTATE_H__

#include <time.h>
#include "actor.h"
#include "map.h"
#include "scenario.h"

// The playstate keeps track of the map, the game actors, the scenario, time, play
// turn count etc.
struct playstate {
  struct map_state map_state;     // The map as shown
  struct list aerodromes;         // List of all aerodromes
  struct list flights;            // Fligths in motion
  struct list dogfights;          // Active dogfights
  struct list free_memory;        // List of memory to be recycled
  struct scenario *scenario;      // The active scenario, or NULL
  struct list accomplished;       // List of accomplished objectives, or state objects
                                  // related to it (partial accomplishments)
  unsigned turn;                  // Number of turns played
  struct playfield *playfield;    // Information about the playfield (map) being played.
  struct tm current_time;
  struct list downed_allied;      // Downed allied airplanes
  struct list downed_central;     // Downed central powers airplanes
};

// **********************************************************************

struct playstate *active_playstate;
extern struct playstate *new_playstate(void);
extern void recycle_memory(struct playstate *ps);

#endif // __PLAYSTATE_H__

#ifndef __SCENARIO_H__
#define __SCENARIO_H__

#include <stdbool.h>
#include <time.h>
#include "list.h"

// Forward declations
struct playstate;

struct scenario {
  struct node node;
  const char *title;
  const char *description;  // Long desciptive text of the scenario
  struct tm start;          // Start date and time
  struct playfield *playfield; // Information about the playfield (map) being played
  void (*setup)(struct playstate*); // Set up the playstate
  bool (*playturn)(struct playstate *);
  void (*summarize)(struct playstate *);
};

struct scenarios {
  struct list trainer_scenarios;
  struct list normal_scenarios;
};

// **********************************************************************

extern struct scenarios *initialize_scenarios(void);
extern struct scenario *select_a_game(struct scenarios*);

#endif // __SCENARIO_H__

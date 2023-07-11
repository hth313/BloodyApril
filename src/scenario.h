#ifndef __SCENARIO_H__
#define __SCENARIO_H__

#include <stdbool.h>
#include <time.h>
#include "list.h"
#include "playstate.h"

struct playstate;

typedef void (*fptr_setup)(struct playstate *);
typedef bool (*fptr_playturn)(struct playstate *);
typedef void (*fptr_summarize)(struct playstate *);

struct scenario {
  struct node node;
  const char *description;  // Long desciptive text of the scenario
  struct tm start;          // Start date and time
  fptr_setup setup;         // Set up the playstate
  fptr_playturn playturn;   // Execute a single playturn, false to
  fptr_summarize summarize; // Summarize the outcome of the game.
};

struct scenarios {
  struct list trainer_scenarios;
  struct list normal_scenarios;
};

// **********************************************************************

struct scenarios *initialize_scenarios(void);

#endif // __SCENARIO_H__

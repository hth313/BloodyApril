#ifndef __SCENARIO_EXPLORE_MAP_H__
#define __SCENARIO_EXPLORE_MAP_H__

#include <stdbool.h>
#include "scenario.h"


// **********************************************************************

extern void explore_map_setup(struct playstate *playstate);
extern bool playturn_explore_map(struct playstate *);
extern void summarize_explore_map(struct playstate *);

#endif // __SCENARIO_EXPLORE_MAP_H__

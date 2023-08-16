#ifndef __SCENARIO_DOGFIGHT_H__
#define __SCENARIO_DOGFIGHT_H__

#include <stdbool.h>
#include "../scenario.h"

// **********************************************************************

extern void basic_dogfight_setup(struct playstate *);
extern bool playturn_dogfight_only(struct playstate *);
extern void summarize_dogfight_only(struct playstate *);

#endif // __SCENARIO_DOGFIGHT_H__

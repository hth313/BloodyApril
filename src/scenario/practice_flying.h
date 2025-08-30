#ifndef __SCENARIO_PRACTICE_FLYING_H__
#define __SCENARIO_PRACTICE_FLYING_H__

#include <stdbool.h>
#include "../scenario.h"

// **********************************************************************

extern void practice_flying_setup(struct playstate *);
extern bool practice_flying_playturn(struct playstate *);
extern void practice_flying_summarize(struct playstate *);

#endif // __SCENARIO_PRACTICE_FLYING_H__

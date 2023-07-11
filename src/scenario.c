#include "memory.h"
#include "scenario.h"
#include "scenario/dogfight.h"
#include <time.h>

struct scenario basic_dogfight = {
    .description = "Try a dogfight, your flight has engaged some opponents.\n"
                   "You (the allied) are attacked by some opponents.\n"
                   "Participants from a squadron and an opposing Jasta are "
                   "randomly selected.\n",
    .start = { .tm_year = 1917, .tm_mon = 3, .tm_hour = 12 },
    .setup = basic_dogfight_setup,
    .playturn = playturn_dogfight_only,
    .summarize = summarize_dogfight_only
}


struct scenarios *initialize_scenarios(void) {
  struct scenarios *p = safe_malloc(sizeof(struct scenarios));
  init_list(&p->trainer_scenarios);
  init_list(&p->normal_scenarios);

  add_tail(&p->trainer_scenarios.basic_dogfight);

  return p;
}

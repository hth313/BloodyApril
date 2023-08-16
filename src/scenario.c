#include "memory.h"
#include "scenario.h"
#include "scenario/scenario_dogfight.h"
#include <time.h>

struct scenario basic_dogfight = (struct scenario) {
    .title = "Try a dogfight",
    .description = "Try a separate dogfight where your allied flight engage some opponents.\n"
                   "The participants from a squadron and an opposing Jasta are "
                   "randomly selected.\n",
    .start = { .tm_year = 17, .tm_mon = 3, .tm_mday = 10, .tm_hour = 12, .tm_wday = 2 },
    .setup = basic_dogfight_setup,
    .playturn = playturn_dogfight_only,
    .summarize = summarize_dogfight_only
};


struct scenarios *initialize_scenarios(void) {
  struct scenarios *p = safe_malloc(sizeof(struct scenarios));
  init_list(&p->trainer_scenarios);
  init_list(&p->normal_scenarios);

  add_tail(&p->trainer_scenarios.basic_dogfight);

  return p;
}

#include "memory.h"
#include "scenario.h"
#include "practice_flying.h"
#include "scenario_dogfight.h"
#include "scenario_explore_map.h"
#include <time.h>

static struct scenario practice_flying = (struct scenario) {
    .title = "Practice takeoff and landing",
    .description = "Take off from one aerodrme, fly to another one and land successfully",
    .start = { .tm_year = 17, .tm_mon = 3, .tm_mday = 10, .tm_hour = 12, .tm_wday = 2 },
    .setup = practice_flying_setup,
    .playturn = playturn_dogfight_only,
    .summarize = practice_flying_summarize
};

static struct scenario basic_dogfight = (struct scenario) {
    .title = "Try a dogfight",
    .description = "Try a separate dogfight where your allied flight engage some opponents.\n"
                   "The participants from a squadron and an opposing Jasta are "
                   "randomly selected.\n",
    .start = { .tm_year = 17, .tm_mon = 3, .tm_mday = 10, .tm_hour = 12, .tm_wday = 2 },
    .setup = basic_dogfight_setup,
    .playturn = playturn_dogfight_only,
    .summarize = summarize_dogfight_only
};

static struct scenario explore_map = (struct scenario) {
  .title = "Move around on the map",
  .description = "For initial debugging of the map coordinates and scrolling.\n",
    .start = { .tm_year = 17, .tm_mon = 3, .tm_mday = 10, .tm_hour = 12, .tm_wday = 2 },
    .setup = explore_map_setup,
    .playturn = playturn_explore_map,
    .summarize = summarize_explore_map
};


struct scenarios *initialize_scenarios(void) {
  struct scenarios *p = safe_malloc(sizeof(struct scenarios));
  init_list(&p->trainer_scenarios);
  init_list(&p->normal_scenarios);

  add_tail(&p->trainer_scenarios, &practice_flying.node);
  add_tail(&p->trainer_scenarios, &basic_dogfight.node);
  add_tail(&p->trainer_scenarios, &explore_map.node);

  return p;
}

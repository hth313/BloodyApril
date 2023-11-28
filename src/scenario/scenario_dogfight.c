#include "scenario_dogfight.h"
#include "../dogfight.h"
#include "../playstate.h"

void basic_dogfight_setup(struct playstate *playstate) {
}

bool playturn_dogfight_only(struct playstate *playstate) {
  return dogfight((struct dogfight*)&playstate->dogfights.head);
}

void summarize_dogfight_only(struct playstate *playstate) {
}

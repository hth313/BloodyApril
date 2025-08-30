#include "aerodrome.h"
#include "practice_flying.h"
#include "playstate.h"

void practice_flying_setup(struct playstate *playstate) {
  create_aerodromes(playstate);
  create_weather(playstate);
}

void practice_flying_summarize(struct playstate *playstate) {
  // TODO: detect landing, safely or not
}

bool practice_flying_playturn(struct playstate *playstate) {
  return true;
}

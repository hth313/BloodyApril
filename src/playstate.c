#include "actor.h"
#include "list.h"
#include "memory.h"
#include "playstate.h"
#include "scenario.h"

struct playstate *new_playstate(void) {
  struct playstate *state =
      (struct playstate *) safe_malloc(sizeof(struct playstate));
  state->actors = new_actorsmap();
  init_list(&state->map_visuals);
  init_list(&state->aerodromes);
  init_list(&state->flights);
  init_list(&state->dogfights);
  state->scenario = NULL;
  init_list(&state->accomplished);
  init_list(&state->downed_allied);
  init_list(&state->downed_central);
  return state;
}

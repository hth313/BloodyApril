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
  init_list(&state->free_memory);
  state->scenario = NULL;
  init_list(&state->accomplished);
  init_list(&state->downed_allied);
  init_list(&state->downed_central);
  return state;
}

// Due to synchronization, memory for objects that is part of the actor display
// list cannot be free() while being part of the display.
// The idea is that we unlink the actor from its owner, be it the map or the
// flights or digfight list of playstate. Then after next synchronization with
// the interrupt that builds the display list, it will no longer be part of
// that list and we can recycle the memory. This function does that job.
void recycle_memory(struct playstate *ps) {
  struct node *node;
  struct node *next;
  foreach_node_safe(&ps->free_memory, node, next) { free(node); }
}

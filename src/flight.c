// A flight is a collection of airplanes. While many entities are allocated
// statically, flights are dynamaically allocated from the heap.
// This is to allow a certain level of flexibility, such as allowing for
// merging flights of different squadrons when they operate together and
// to allow them to split up in case of separation, which may be that they
// are heading to different aerodromes or possibly handle that a single
// or a few airplanes are separated from a flight due to combat outcome
// (lose track of each others).

#include <stdlib.h>
#include "actor_visual.h"
#include "airplane.h"
#include "flight.h"
#include "list.h"
#include "memory.h"
#include "playstate.h"

// A sequence number, mainly to ensure the order in a list is kept consistent
// even when a node is removed and later added again.
static int sequence;

// Create a new flight. This will initialize most fields except for
// that it should be immediately linked into its owning list.
struct flight *new_flight(location loc, direction heading, struct sprite *sprite) {
  struct flight *p = (struct flight*) safe_malloc(sizeof(struct flight));
  p->node.kind = Flight;
  p->node.order = sequence++;
  init_list(&p->airplanes);
  p->loc = loc;
  p->heading = heading;
  p->move_order = MOVE_ORDER_LEVEL;
  p->detection = Undetected;
  add_visual_loc(&p->visual, loc, sprite);
  p->visual.node.kind = Flight;
  p->visual.flight = p;
  return p;
}

// Unlink a flight from its owning list and recycle its storage.
void drop_flight(struct playstate *ps, struct flight *p) {
  remove_node(&p->node.node);
  add_tail(&ps->free_memory, &p->node.node);
}

bool prune_downed(struct playstate *ps, struct flight *flight) {
  airplane *p;
  struct airplane *next;
  foreach_node_safe(&flight->airplanes, p, next) {
    if ((p->property & AIRPLANE_DOWNED)) {
      remove_node( (struct node*) p);
      if (flight->allied) {
	add_tail(&ps->downed_allied, (struct node*) p);
      } else {
	add_tail(&ps->downed_central, (struct node*) p);
      }
    }
  }
  if (empty_list(&flight->airplanes)) {
    drop_flight(ps, flight);
    return true;   // all dropped
  } else {
    return false;
  }
}

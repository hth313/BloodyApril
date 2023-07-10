// A flight is a collection of airplanes. While many entities are allocated
// statically, flights are dynamaically allocated from the heap.
// This is to allow a certain level of flexibility, such as allowing for
// merging flights of different squadrons when they operate together and
// to allow them to split up in case of separation, which may be that they
// are heading to different aerodromes or possibly handle that a single
// or a few airplanes are separated from a flight due to combat outcome
// (lose track of each others).

#include <stdlib.h>
#include "flight.h"
#include "list.h"

// Create a new flight. This will initialize most fields except for
// that it should be immediately linked into its owning list.
flight *new_flight(location* position, direction heading) {
  flight *p = safe_malloc(sizeof(flight));
  p->typed_node.node_kind = Flight;
  init_list(&p->airplanes);
  p->position = position;
  p->heading = heading;
  p->move_order = MOVE_ORDER_LEVEL;
  return p;
}

// Unlink a flight from its owning list and recycle its storage.
void drop_flight(flight *p) {
  remove_node(&flight.typed_node);
  free(p);
}

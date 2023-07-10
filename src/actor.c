#include "actor.h"
#include "hashmap.h"
#include "list.h"
#include "memory.h"

struct list *add_actor(all_actors *map, coordinate pos, struct node_kind *node) {
  struct actors *p = hashmap_get(map, &coordinate);
  if (!p) {
    p = safe_malloc(sizeof(struct actors));
    p->coordinate = coordinate;
    init_list(&p->actors);
    hashmap_set(map, p);
  }
  add_tail(&p->actors, node);
  return &p->actors;
}

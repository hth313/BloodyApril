#include "actor.h"
#include "hashmap.h"
#include "list.h"
#include "memory.h"

struct list *add_actor(actorsmap *map, coordinate pos, struct typed_node *node) {
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

void unlink_actor(actorsmap *map, coordinate pos, struct typed_node *node) {
  struct actors *p = hashmap_get(map, &coordinate);
  if (p != NULL) {
    remove_node(node);
    if (empty_list(&p->actors)) {
      hashmap_delete(p);
      free(p);
    }
  }
}

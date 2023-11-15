#include "actor.h"
#include "list.h"
#include "memory.h"

struct list *add_actor(actorsmap map, coordinate pos, struct typed_node *tnode) {
  struct actors_pos *p = hashmap_get(map, &pos);
  if (!p) {
    p = safe_malloc(sizeof(struct actors_pos));
    p->pos = pos;
    init_list(&p->actors);
    hashmap_set(map, p);
  }
  add_tail(&p->actors, &tnode->node);
  return &p->actors;
}

void unlink_actor(actorsmap map, coordinate pos, struct typed_node *tnode) {
  struct actors_pos *p = hashmap_get(map, &pos);
  if (p != NULL) {
    remove_node(&tnode->node);
    if (empty_list(&p->actors)) {
      hashmap_delete(map, p);
      free(p);
    }
  }
}

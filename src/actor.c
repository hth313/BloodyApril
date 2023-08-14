#include "actor.h"
#include "hashmap.h"
#include "list.h"
#include "memory.h"

static uint64_t elt_hash(const void *item, uint64_t seed0, uint64_t seed1) {
  struct actor_pos *p = (struct actor_pos *)item;
  return hashmap_sip(&p->pos.qr, sizeof p->pos.qr, seed0, seed1);
}

static void elt_free(void *item) {
  struct actor_pos *p = (struct actor_pos *)item;
  struct node *current;
  struct node *next;
  foreach_node_safe(&p->actors, current, next) { free(current); }
}

static int elt_compare(const void *a, const void *b, void *udata) {
  struct actor_pos *ap = (struct actor_pos *)a;
  struct actor_pos *bp = (struct actor_pos *)b;
  return ap->pos.qr - bp->pos.qr;
}

actorsmap new_actorsmap(void) {
  return (actorsmap) hashmap_new(sizeof(struct actors_pos), 0, 0, 0,
				 elt_hash, elt_compare, elt_free, NULL);
}

struct list *add_actor(actorsmap map, coordinate pos, struct typed_node *node) {
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

void unlink_actor(actorsmap map, coordinate pos, struct typed_node *node) {
  struct actors *p = hashmap_get(map, &coordinate);
  if (p != NULL) {
    remove_node(node);
    if (empty_list(&p->actors)) {
      hashmap_delete(p);
      free(p);
    }
  }
}

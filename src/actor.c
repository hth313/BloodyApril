#include "actor.h"
#include "hashmap.h"
#include "list.h"
#include "memory.h"

static uint64_t elt_hash(const void *item, uint64_t seed0, uint64_t seed1) {
  struct actors_pos *p = (struct actors_pos *)item;
  return hashmap_sip(&p->pos.qr, sizeof p->pos.qr, seed0, seed1);
}

static void elt_free(void *item) {
  struct actors_pos *p = (struct actors_pos *)item;
  struct node *current;
  struct node *next;
  foreach_node_safe(&p->actors, current, next) { free(current); }
}

static int elt_compare(const void *a, const void *b, void *udata) {
  struct actors_pos *ap = (struct actors_pos *)a;
  struct actors_pos *bp = (struct actors_pos *)b;
  return ap->pos.qr - bp->pos.qr;
}

actorsmap new_actorsmap(void) {
  return (actorsmap) hashmap_new(sizeof(struct actors_pos), 0, 0, 0,
				 elt_hash, elt_compare, elt_free, NULL);
}

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

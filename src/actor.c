#include "actor.h"
#include "list.h"
#include "map.h"

struct list *add_actor(coordinate pos, struct actor_visual *actor_visual) {
  struct list *list = sector_data[pos.q][pos.r].actors;
  if (list == 0) {
    list = alloc_actor_list();
    init_list(list);
    sector_data[pos.q][pos.r].actors = list;
  }
  add_tail(list, &actor_visual->node);
  q_actor_count[pos.q]++;
  return list;
}

void unlink_actor(coordinate pos, struct actor_visual *actor_visual) {
  remove_node(&actor_visual->node);
  struct list *list = sector_data[pos.q][pos.r].actors;
  if (empty_list(list)) {
    vacate_sector(pos);
    sector_data[pos.q][pos.r].actors = 0;
  }
  q_actor_count[pos.q]--;
}

#include "actor_visual.h"
#include <foenix/vicky.h>

// This list holds the elements in sort order. As objects move elements
// are pushed in that direction in the list to keep them in reasonable
// sort order. In reality, as we expect there are a decent amount of
// sprites the order does not need to be perfect, trickling should suffice.
static struct list visuals;

static uint16_t offset_x;
static uint16_t offset_y;
static struct actor_visual *head_actor;
static struct actor_visual *next_actor;

static bool is_visible(struct actor_visual *p) {
  return p->y > offset_y;
}

static void assign_sprite(unsigned index, struct actor_visual *p) {
  struct sprite *sprite = &Sprite[next_sprite];
  sprite.control = next_actor->sprite.control;
  sprite.addy_high = next_actor->sprite.addy_high;
  sprite.x = next_actor->show_x - offset_x;
  sprite.y = next_actor->show_y - offset_y;
  next_actor->sprite_index = index;
}

static void enable_sol(void) {
  if (head_actor->succ) {
    unsigned line = head_actor->y - offset_y + SPRITE_HEIGHT;
    vicky.line_interrupt[0].control = 1 | (line << 4);
  }
}

__attribute__((interrupt)) void sof_handler(void) {
  InterruptController.pending.vicky = INT_VICKY_SOF;  // acknowledge
  vicky.line_interrupt[0].control = 0;                // no sol interrupt
  unsigned next_sprite = SPRITE_COUNT - 1;
  next_actor = (struct actor_visual *)visuals.head;

  if (!empty_list(&visuals)) {
    // Update positions and allow actors to trickle position in the list.
    unsigned y = next_actor->y;

    struct actor_visual *current;
    struct actor_visual *next;
    foreach_node_safe(&visuals, current, next) {
      current->show_x = current->x;
      current->show_y = current->y;
      if (current->show_y < y) {
        // Move the node back one step
	struct node *pred = current->pred;
        remove_node(current);
	insert_before(pred, current);
      } else if (next->y < y) {
        // Move the current node forward
        remove_node(current);
	insert_after(next, current);
      }
      y = current->show_y;
    }

    // Skip over initial sprites that are not visible, then allocate sprites
    // until we have no more or we run out of actors.
    while (next_actor->succ) {
      if (is_visible(next_actor)) {
        if (next_sprite == first_active_sprite) {
          enable_sol();
	  break;
	}
	next_sprite++;
	if (next_sprite == SPRITE_COUNT) {
	  next_sprite = 0;
        }
        assign_sprite(next_sprite, next_actor);
        if (next_sprite == 0) {
	  // Set the first one assigned.
          head_actor = next_actor;
	}
      }
      next_actor = next_actor->succ;
    }
  }

  // Disable rest of sprites (if we did not use them all up)
  for (unsigned i = next_sprite; i < SPRITE_COUNT; i++) {
    Sprite[i].control = 0;
  }
}

__attribute__((interrupt)) void sol_handler(void) {
  InterruptController.pending.vicky = INT_VICKY_SOL;  // acknowledge
  while (head_actor->succ && next_actor->succ) {
    if (line >= head_actor->y - offset_y + SPRITE_HEIGHT) {
      // We can reuse this one
      unsigned index = head_actor->sprite_index;
      head_actor = head_actor->next;
      assign_sprite(index, next_actor);
      next_actor = next_actor->succ;
    } else {
      break;
    }
  }
  if (next_actor->succ) {
    enable_sol();
  }
}

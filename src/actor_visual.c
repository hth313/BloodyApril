#include "actor_visual.h"
#include "actor.h"
#include "dogfight.h"
#include "flight.h"
#include "list.h"
#include "playstate.h"
#include "scenario.h"
#include <foenix/interrupt.h>
#include <foenix/vicky.h>
#include <mcp/interrupt.h>
#include <mcp/syscalls.h>
#include <stdint.h>
#include <signal.h>

// This list holds the elements in sort order. As objects move elements
// are pushed in that direction in the list to keep them in reasonable
// sort order. In reality, as we expect there are a decent amount of
// sprites the order does not need to be perfect, trickling should suffice.
// Note that this list can either be map items or a list of dogfight
// particpants, it is meant to point to the list that is shown in the display.
static struct list actor_visuals;

static uint16_t offset_x;
static uint16_t offset_y;
static struct actor_visual *head_actor;
static struct actor_visual *next_actor;
static unsigned scan_line;
static unsigned image_index;  // used for blinking/animated sprites

// This flag is set when the main loop is waiting for the
// sof_handler to rebuild the actor list. The sof_handler
// acknowledge it by clearing it.
static sig_atomic_t rebuild_actor_visuals;

#define SCAN_LINE_MARGIN (SPRITE_HEIGHT >> 1)

static bool is_visible(struct actor_visual *p) {
  return p->y > offset_y;
}

static void assign_sprite(unsigned index, struct actor_visual *p) {
  volatile struct sprite *sprite = &Sprite[index];
  sprite->control = next_actor->sprite[image_index].control;
  sprite->addy_high = next_actor->sprite[image_index].addy_high;
  sprite->x = next_actor->show_x + next_actor->staggered - offset_x;
  sprite->y = next_actor->show_y + next_actor->staggered - offset_y;
  next_actor->sprite_index = index;
}

static void enable_sol(void) {
  if (head_actor->node.node.succ) {
    struct actor_visual *pred = (struct actor_visual*) next_actor->node.node.pred;
    unsigned line = pred->y - SCAN_LINE_MARGIN;
    unsigned minimum_skip = scan_line + SCAN_LINE_MARGIN * 2;
    if (line < minimum_skip) {
      line = minimum_skip;
    }
    Vicky.line_interrupt[0].control = 1 | (line << 4);
    scan_line = line;
  }
}

static bool y_pred(struct node *current_node,
                   struct node *next,
                   struct node *new_item) {
  struct actor_visual *next_node = (struct actor_visual *) next;
  struct actor_visual *new_node = (struct actor_visual *) new_item;

  if (next_node->y == new_node->y) {
    // Same vertical location, use node priority (ignore x location)
    if (next_node->node.kind == new_node->node.kind) {
      return next_node->node.order >= new_node->node.order;
    } else {
      return next_node->node.kind >= new_node->node.kind;
    }
  }

  return next_node->y >= new_node->y;
}

// After adjust the visual list, examine nodes before and after to see if
// they have the same location, in the case stagger them.
static void adjust_stagger(struct actor_visual *p) {
  struct actor_visual *pred = (struct actor_visual *)p->node.node.pred;
  // Recursively step back to the first node at this location
  if (pred->node.node.pred != 0 && pred->show_y == p->show_y &&
      pred->show_x == p->show_x) {
    adjust_stagger(pred);
  } else {
    unsigned staggered = 0;
    struct actor_visual *next;
    while ((next = (struct actor_visual *)p->node.node.succ) &&
           next->node.node.succ &&
           p->show_y == next->show_y &&
           p->show_x == next->show_x) {
      p->staggered = staggered;
      staggered += 4;
      p = next;
    }
  }
}

static void insert_actor(struct actor_visual *p) {
  predicate_insert(&actor_visuals, &p->node.node, y_pred);
  adjust_stagger(p);
}

static bool insert_actors(struct actors_pos *p, void *data) {
  struct generic_actor *actor;
  foreach_node(&p->actors, actor) { insert_actor(actor); }
  return true;
}

__attribute__((interrupt)) void sof_handler(void) {
  // acknowledge interrupt
  InterruptController.pending.vicky = INT_VICKY_SOF;

  // no sol interrupt
  Vicky.line_interrupt[0].control = 0;

  if (rebuild_actor_visuals) {
    rebuild_actor_visuals = 0; // acknowledge
    init_list(&actor_visuals); // clear list

    // Add actors from map
    hashmap_scan(active_playstate->actors, insert_actors, 0);

    // Add flights
    struct flight *flight;
    foreach_node(&active_playstate->flights, flight) {
      insert_actor(&flight->visual);
    }

    // Add dogfights
    struct dogfight *dogfight;
    foreach_node(&active_playstate->dogfights, dogfight) {
      insert_actor(&dogfight->visual);
    }
  }

  scan_line = 0;
  unsigned next_sprite = SPRITE_COUNT - 1;
  next_actor = (struct actor_visual *)actor_visuals.head;

  if (!empty_list(&actor_visuals)) {

  // The follow code attempts to readjust list if actors
  // were moved. This is not needed if we regenerate the map.
  // Keep the code for now in case the way of laying them
  // out does not work, then this can be considered again.

#if 0
    // Update positions and allow actors to trickle position in the list.
    unsigned y = next_actor->y;

    struct actor_visual *current;
    struct actor_visual *next;
    foreach_node_safe(&actor_visuals, current, next) {
      current->show_x = current->x;
      current->show_y = current->y;
      if (current->show_y < y) {
        // Move the node back one step
	struct node *pred = current->node.node.pred;
        remove_node((struct node*)current);
	insert_before(pred, current);
      } else if (next->y < y) {
        // Move the current node forward
        remove_node(&current->node.node);
	insert_after(&next->node.node, &current->node.node);
      }
      y = current->show_y;
    }
#endif

    // Skip over initial sprites that are not visible, then allocate sprites
    // until we have no more or we run out of actors.
    unsigned count = SPRITE_COUNT;
    while (next_actor->node.node.succ) {
      if (is_visible(next_actor)) {
        if (count == 0) {
          enable_sol();
	  break;
	}
        next_sprite++;
	count--;
	if (next_sprite == SPRITE_COUNT) {
	  next_sprite = 0;
        }
        assign_sprite(next_sprite, next_actor);
        if (next_sprite == 0) {
	  // Set the first one assigned.
          head_actor = next_actor;
	}
      }
      next_actor = (struct actor_visual *) next_actor->node.node.succ;
    }
  }

  // Disable rest of sprites (if we did not use them all up)
  for (unsigned i = next_sprite; i < SPRITE_COUNT; i++) {
    Sprite[i].control = 0;
  }
}

__attribute__((interrupt)) void sol_handler(void) {
  InterruptController.pending.vicky = INT_VICKY_SOL;  // acknowledge
  while (head_actor->node.node.succ && next_actor->node.node.succ) {
    if (scan_line >= head_actor->y - offset_y + SPRITE_HEIGHT) {
      // We can reuse this one
      unsigned index = head_actor->sprite_index;
      head_actor = (struct actor_visual *) head_actor->node.node.succ;
      assign_sprite(index, next_actor);
      next_actor = (struct actor_visual *) next_actor->node.node.succ;
    } else {
      break;
    }
  }
  if (next_actor->node.node.succ) {
    enable_sol();
  }
}

static p_int_handler old_sof_handler;
static p_int_handler old_sol_handler;

void install_interrupt_handlers(void) {
  init_list(&actor_visuals);
  old_sof_handler = sys_int_register(INT_SOF_A, sof_handler);
  old_sol_handler = sys_int_register(INT_SOL_A, sol_handler);
}

void restore_interrupt_handlers(void) {
  sys_int_register(INT_SOF_A, old_sof_handler);
  sys_int_register(INT_SOL_A, old_sol_handler);
}

void add_visual_loc(struct actor_visual *p, location loc,
                struct sprite *sprite) {
  uint16_t x = loc_pixel_x(loc);
  uint16_t y = loc_pixel_y(loc);
  add_visual_xy(p, x, y, sprite);
}

void add_visual_coord(struct actor_visual *p, coordinate coord,
                struct sprite *sprite) {
  uint16_t x = pixel_x(coord);
  uint16_t y = pixel_y(coord);
  add_visual_xy(p, x, y, sprite);
}

void add_visual_xy(struct actor_visual *p, uint16_t x,
                   uint16_t y, struct sprite *sprite) {
  p->x = x;
  p->y = y;
  p->sprite[0] = *sprite;
}

// Inform interrupt to rebuild the display list of actors.
// Will wait until the interrupt has reinitialized the list which should
// take at most one frame (1/50 - 1/70) of a second.
// At this point we can reclaim memory waiting to be freed.
void rebuild_actor_visual_list(struct playstate *ps) {
  rebuild_actor_visuals = 1;
  while (rebuild_actor_visuals)
    ;
  recycle_memory(ps);
}

#include "actor_visual.h"
#include <foenix/interrupt.h>
#include <foenix/vicky.h>
#include <mcp/interrupt.h>
#include <mcp/syscalls.h>
#include <stdint.h>

// This list holds the elements in sort order. As objects move elements
// are pushed in that direction in the list to keep them in reasonable
// sort order. In reality, as we expect there are a decent amount of
// sprites the order does not need to be perfect, trickling should suffice.
// Note that this list can either be map items or a list of dogfight
// particpants, it is meant to point to the list that is shown in the display.
static struct list *visuals;

static uint16_t offset_x;
static uint16_t offset_y;
static struct actor_visual *head_actor;
static struct actor_visual *next_actor;
static unsigned scan_line;

#define SCAN_LINE_MARGIN (SPRITE_HEIGHT >> 1)

static bool is_visible(struct actor_visual *p) {
  return p->y > offset_y;
}

static void assign_sprite(unsigned index, struct actor_visual *p) {
  volatile struct sprite *sprite = &Sprite[index];
  sprite->control = next_actor->sprite.control;
  sprite->addy_high = next_actor->sprite.addy_high;
  sprite->x = next_actor->show_x - offset_x;
  sprite->y = next_actor->show_y - offset_y;
  next_actor->sprite_index = index;
}

static void enable_sol(void) {
  if (head_actor->node.succ) {
    struct actor_visual *pred = (struct actor_visual*) next_actor->node.pred;
    unsigned line = pred->y - SCAN_LINE_MARGIN;
    unsigned minimum_skip = scan_line + SCAN_LINE_MARGIN * 2;
    if (line < minimum_skip) {
      line = minimum_skip;
    }
    Vicky.line_interrupt[0].control = 1 | (line << 4);
    scan_line = line;
  }
}

__attribute__((interrupt)) void sof_handler(void) {
  InterruptController.pending.vicky = INT_VICKY_SOF;  // acknowledge
  Vicky.line_interrupt[0].control = 0;                // no sol interrupt
  scan_line = 0;
  unsigned next_sprite = SPRITE_COUNT - 1;
  next_actor = (struct actor_visual *)visuals->head;

  if (!empty_list(visuals)) {
    // Update positions and allow actors to trickle position in the list.
    unsigned y = next_actor->y;

    struct actor_visual *current;
    struct actor_visual *next;
    foreach_node_safe(visuals, current, next) {
      current->show_x = current->x;
      current->show_y = current->y;
      if (current->show_y < y) {
        // Move the node back one step
	struct node *pred = current->node.pred;
        remove_node((struct node*)current);
	insert_before(pred, current);
      } else if (next->y < y) {
        // Move the current node forward
        remove_node(&current->node);
	insert_after(&next->node, &current->node);
      }
      y = current->show_y;
    }

    // Skip over initial sprites that are not visible, then allocate sprites
    // until we have no more or we run out of actors.
    unsigned count = SPRITE_COUNT;
    while (next_actor->node.succ) {
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
      next_actor = (struct actor_visual *) next_actor->node.succ;
    }
  }

  // Disable rest of sprites (if we did not use them all up)
  for (unsigned i = next_sprite; i < SPRITE_COUNT; i++) {
    Sprite[i].control = 0;
  }
}

__attribute__((interrupt)) void sol_handler(void) {
  InterruptController.pending.vicky = INT_VICKY_SOL;  // acknowledge
  while (head_actor->node.succ && next_actor->node.succ) {
    if (scan_line >= head_actor->y - offset_y + SPRITE_HEIGHT) {
      // We can reuse this one
      unsigned index = head_actor->sprite_index;
      head_actor = (struct actor_visual *) head_actor->node.succ;
      assign_sprite(index, next_actor);
      next_actor = (struct actor_visual *) next_actor->node.succ;
    } else {
      break;
    }
  }
  if (next_actor->node.succ) {
    enable_sol();
  }
}

static p_int_handler old_sof_handler;
static p_int_handler old_sol_handler;

void install_interrupt_handlers(void) {
  old_sof_handler = sys_int_register(INT_SOF_A, sof_handler);
  old_sol_handler = sys_int_register(INT_SOL_A, sol_handler);
}

void restore_interrupt_handlers(void) {
  sys_int_register(INT_SOF_A, old_sof_handler);
  sys_int_register(INT_SOL_A, old_sol_handler);
}

static bool y_pred(struct node *current_node,
                   struct node *next,
                   struct node *new_item) {
  struct actor_visual *next_node = (struct actor_visual *) next;
  struct actor_visual *new_node = (struct actor_visual *) new_item;

  return next_node->y >= new_node->y;
}

static void insert_actor(struct list *visuals, struct actor_visual *p) {
  predicate_insert(visuals, &p->node, y_pred);
}

void add_visual(struct list *visuals, struct actor_visual *p, location loc,
                struct sprite *sprite) {
  uint16_t x, y;
  location_to_pixel_pos(loc, &x, &y);
  add_visual_xy(visuals, p, x, y, sprite);
}

void add_visual_xy(struct list *visuals, struct actor_visual *p, uint16_t x,
                   uint16_t y, struct sprite *sprite) {
  p->x = x;
  p->y = y;
  p->sprite = *sprite;
  //  atomically(insert_actor, p);
  insert_actor(visuals, p);
}

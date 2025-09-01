#include "system.h"
#include "actor_visual.h"
#include "actor.h"
#include "aerodrome.h"
#include "dogfight.h"
#include "flight.h"
#include "list.h"
#include "playstate.h"
#include "scenario.h"
#include <stdint.h>
#include <signal.h>

#ifdef __CALYPSI_TARGET_SYSTEM_A2560U__
#include <foenix/interrupt.h>
#include <foenix/vicky.h>
#include <mcp/interrupt.h>
#include <mcp/syscalls.h>
#endif

// Visual actors are sprites placed on a backdrop (game map).
// The map is partially shown, so not every actor that exists may be visible.
// We assign hardware sprites to visible actors in a priority order to control
// how they overlap in a way from the ground up.
//
// From the bottom we have:
// - Aerodromes (these could be drawn on the map, but for now we use sprites)
// - ground actors, like AA units
// - flights, a single one is drawn from a group for now
// - dogfight markers
// - AA fire effects
// - annotations, like texts if we overlay such
//

#define SPRITE_COUNT 64

int sprite_limit_used = SPRITE_COUNT;

struct actor_visual *actor_cache[SPRITE_COUNT];

static bool visible(struct viewport *vp, struct actor_visual *actor_visual) {
  int x = actor_visual->x;
  int y = actor_visual->y;
  return x >= 0 && y >= 0 && x < vp->width && y < vp->height;
}

static int place(struct playstate *playstate, struct actor_visual *visual, int index) {
  if (visible(&playstate->map_state.viewport, visual)) {
    if (actor_cache[index] != visual) {
      actor_cache[index] = visual;
      volatile VRAM struct sprite *sprite = &Sprite[index];
      *sprite = visual->actor_tile;
      sprite->x = visual->x - playstate->map_state.viewport.x;
      sprite->y = visual->y - playstate->map_state.viewport.y;
      --index;
    }
  }
  return index;
}

void render(struct playstate *playstate) {
  int index = SPRITE_COUNT - 1;

  // Place visible aerodromes
  struct aerodrome *aerodrome;
  foreach_node(&playstate->aerodromes, aerodrome) {
    index = place(playstate, &aerodrome->visual, index);
    if (index < 0) goto out_of_sprites;
  }

  // Place ground actors
  struct generic_actor *actor;
  foreach_node(&playstate->ground_units, actor) {
    index = place(playstate, &actor->visual, index);
    if (index < 0) goto out_of_sprites;
  }

  // Place airborne actors
  foreach_node(&playstate->air_units, actor) {
    index = place(playstate, &actor->visual, index);
    if (index < 0) goto out_of_sprites;
  }

  // Flights on ground level
  struct flight *flight;
  foreach_node(&playstate->flights, flight) {
    if (flight->altitude == 0) {
      index = place(playstate, &flight->visual, index);
      if (index < 0) goto out_of_sprites;
    }
  }

  // Flights at fairly low level
  foreach_node(&playstate->flights, flight) {
    if (flight->altitude > 0 && flight->altitude < 8) {
      index = place(playstate, &flight->visual, index);
      if (index < 0) goto out_of_sprites;
    }
  }

  // Remaining flights
  foreach_node(&playstate->flights, flight) {
    if (flight->altitude > 8) {
      index = place(playstate, &flight->visual, index);
      if (index < 0) goto out_of_sprites;
    }
  }

  struct dogfight *dogfight;
  foreach_node(&playstate->dogfights, dogfight) {
    index = place(playstate, &dogfight->visual, index);
    if (index < 0) goto out_of_sprites;
  }

out_of_sprites:
  if (index < sprite_limit_used) {
    sprite_limit_used = index;
  }
}

void add_visual_loc(struct actor_visual *p, location loc,
                actor_tile_t *actor_tile) {
  uint16_t x = loc_pixel_x(loc);
  uint16_t y = loc_pixel_y(loc);
  add_visual_xy(p, x, y, actor_tile);
}

void add_visual_coord(struct actor_visual *p, coordinate coord,
                      actor_tile_t *actor_tile) {
  uint16_t x = pixel_x(coord);
  uint16_t y = pixel_y(coord);
  add_visual_xy(p, x, y, actor_tile);
}

void add_visual_xy(struct actor_visual *p, uint16_t x,
                   uint16_t y, actor_tile_t *actor_tile) {
  p->x = x;
  p->y = y;
  p->actor_tile = *actor_tile;
}

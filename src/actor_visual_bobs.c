// Visualize actors on the map. This variant is used for the Amiga where
// we have blitter object on which there is no limitations on how many
// there is.

#include "system.h"
#include "actor_visual.h"
#include "actor.h"
#include "dogfight.h"
#include "flight.h"
#include "list.h"
#include "playstate.h"
#include "scenario.h"
#include <stdint.h>
#include <signal.h>
#include <ACE/managers/viewport/tilebuffer.h>

#define ActorWIdth 32

// This list holds the elements in sort order. We use a primary order that
// is based on the Y location and a secondary order that is priority based.
// Placing them is done in reverse sort order as later bobs overwrite previous
// ones.
static struct list actor_visuals;

static void display_actor(tTileBufferManager *p, struct actor_visual *actor, UWORD stagger) {
  tUwCoordYX camPos = p->pCamera->uPos;
  UWORD x = actor->x + stagger - camPos.uwX;
  UWORD y = actor->y + stagger - camPos.uwY;
  if (x < p->sCommon.pVPort->uwWidth && y < p->sCommon.pVPort->uwHeight) {
    tBob *bob = actor->actor_tile[0];
    bob->sPos.uwX = x;
    bob->sPos.uwY = y;
    bobPush(bob);
  }
}

static void draw_list_of(tTileBufferManager *p, struct list *list) {
  UWORD stagger = (list_length(list) - 1) * 2;
  struct generic_actor *actor;
  foreach_node(list, actor) {
    display_actor(p, &actor->visual, stagger);
    stagger -= 2;
  }
}

void insert_actors(tTileBufferManager *p, struct playstate *playstate,
		   unsigned start_q, unsigned max_q, unsigned start_r,
		   unsigned max_r) {
  bobBegin(p->pScroll->pBack);

  // 1. Draw actors on the map. Traverse the map area covered.
  for (unsigned q = start_q; q < max_q; q++) {
    if (q_actor_count[q] == 0) continue;
    for (unsigned r = start_r; r < max_r; r++) {
      struct list *list = sector_data[q][r].actors;
      if (list != 0) {
	draw_list_of(p, list);
      }
    }
    bobProcessNext();
  }

  // 2. Draw flights on ground in aerodrome.
  draw_list_of(p,  &playstate->aerodromes);
  bobProcessNext();

  // 3. Draw flights, we stagger these to indicate there are more than one in
  // the location. Limit the amount of stagger to be log2(n) so that we get more
  // stagger but it quickly drop off.
  struct flight *flight;
  foreach_node(&playstate->flights, flight) { flight->drawn = false; }
  foreach_node(&playstate->flights, flight) {
    if (!flight->drawn) {
      struct flight *node;
      unsigned stagger = 0;
      foreach_node(&playstate->flights, node) {
	if (location_equal(&node->loc, &flight->loc)) {
	  stagger += 2;
	}
      }
      foreach_node(&playstate->flights, node) {
	stagger -= 2;
	display_actor(p, &node->visual, stagger);
	node->drawn = true;
      }
    }
    bobProcessNext();
  }

  // 4. Draw dogfight on top of everything
  struct dogfight *dogfight;
  foreach_node(&playstate->dogfights, dogfight) { dogfight->drawn = false; }
  foreach_node(&playstate->dogfights, dogfight) {
    if (!dogfight->drawn) {
      struct dogfight *node;
      unsigned stagger = 0;
      foreach_node(&playstate->dogfights, node) {
	if (location_equal(&node->loc, &flight->loc)) {
	  stagger += 2;
	}
      }
      foreach_node(&playstate->dogfights, node) {
	stagger -= 2;
	display_actor(p, &node->visual, stagger);
	node->drawn = true;
      }
    }
    bobProcessNext();
  }

  bobPushingDone();
  bobEnd();
}

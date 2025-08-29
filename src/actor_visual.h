#ifndef __ACTOR_VISUAL_H__
#define __ACTOR_VISUAL_H__

#include "actor_kind.h"
#include "coordinate.h"
#include "system.h"
#include "list.h"

#ifdef __CALYPSI_TARGET_SYSTEM_A2560U__
#include <foenix/vicky.h>
typedef struct sprite actor_tile_t;
#define ACTOR_TILE_HEIGHT 32
#endif

struct aerodrome;
struct archie;
struct artillery;
struct ballon;
struct cavalry;
struct dogfight;
struct flaming_onion;
struct flight;
struct infantry;
struct machine_gun;
struct playstate;

struct actor_visual {
  // Actors are sorted on y position and when occupying the same position
  // based on the kind/order of the node.
  // The 'node.kind' is also used to point back to the owning rich record.
  struct typed_node node; // sorted on kind/order and show_y
  actor_tile_t actor_tile[2]; // actual sprite data to use
  unsigned sprite_index;  // the physical sprite (index) assigned to
  uint16_t prio; // display priority index, 0 is highest, used to ensure order
                 // when staggering
  uint16_t x;             // position is updated here
  uint16_t y;
  uint16_t show_x;        // position for this frame
  uint16_t show_y;
  uint16_t staggered; // adjustment to adjust x/y when stacking, 0/2/4..
  // Pointer to rich data record
  union {
    struct aerodrome *aerodrome;
    struct archie *archie;
    struct artillery *artillery;
    struct ballon *ballon;
    struct cavalry *cavalry;
    struct dogfight *dogfight;
    struct flaming_onion *flaming_onion;
    struct flight *flight;
    struct infantry *infantry;
    struct machine_gun *machine_gun;
  };
};

// **********************************************************************

extern void add_visual_loc(struct actor_visual *, location, actor_tile_t *);
extern void add_visual_coord(struct actor_visual *, coordinate, actor_tile_t *);
extern void add_visual_xy(struct actor_visual *, uint16_t x, uint16_t y, actor_tile_t *);
extern void install_interrupt_handlers(void);
extern void restore_interrupt_handlers(void);
extern void rebuild_actor_visual_list(struct playstate *ps);

extern actor_tile_t *right_facing_dogfight_sprite;
extern actor_tile_t *left_facing_dogfight_sprite;

#endif // __ACTOR_VISUAL_H__

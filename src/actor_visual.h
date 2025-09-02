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
  actor_tile_t actor_tile; // actual sprite data to use
  int sprite_index;  // the physical sprite (index) assigned to
  uint16_t prio; // display priority index, 0 is highest, used to ensure order
                 // when staggering
  uint16_t x;             // position is updated here
  uint16_t y;
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

inline void set_visual_xy(struct actor_visual *p, uint16_t x, uint16_t y) {
  p->x = x;
  p->y = y;
}

inline void set_visual_coord(struct actor_visual *p, coordinate coord) {
  uint16_t x = pixel_x(coord);
  uint16_t y = pixel_y(coord);
  set_visual_xy(p, x, y);
}

inline void set_visual_loc(struct actor_visual *p, location loc) {
  uint16_t x = loc_pixel_x(loc);
  uint16_t y = loc_pixel_y(loc);
  set_visual_xy(p, x, y);
}

extern void invalidate_actor_placement_cache();
extern void render(struct playstate *playstate);

extern actor_tile_t allied_aerodrome_sprite;
extern actor_tile_t central_aerodrome_sprite;
extern actor_tile_t right_facing_dogfight_sprite;
extern actor_tile_t left_facing_dogfight_sprite;

extern actor_tile_t SopwithPup_sprite;
extern actor_tile_t SopwithTriplane_sprite;
extern actor_tile_t Albatros_D5a_J3_sprite;
extern actor_tile_t Albatros_D2_sprite;
extern actor_tile_t Albatros_D2_sprite_red_baron;

#endif // __ACTOR_VISUAL_H__

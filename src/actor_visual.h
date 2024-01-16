#ifndef __ACTOR_VISUAL_H__
#define __ACTOR_VISUAL_H__

#include "actor_kind.h"
#include "coordinate.h"
#include "list.h"

#ifdef __CALYPSI_TARGET_SYSTEM_FOENIX__
#include <foenix/vicky.h>
#endif

#ifdef __CALYPSI_TARGET_SYSTEM_CX16__
#include "x16.h"
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
  uint16_t show_x;        // position for this frame
  uint16_t show_y;
  uint16_t staggered;     // used to adjust x/y when placed on top
  struct sprite sprite[2]; // actual sprite data to be used
  unsigned sprite_index;  // the physical sprite (index) assigned to
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

extern void add_visual_loc(struct actor_visual *, location, struct sprite *);
extern void add_visual_coord(struct actor_visual *, coordinate, struct sprite *);
extern void add_visual_xy(struct actor_visual *, uint16_t x, uint16_t y, struct sprite *);
extern void install_interrupt_handlers(void);
extern void restore_interrupt_handlers(void);
extern void rebuild_actor_visual_list(struct playstate *ps);

#endif // __ACTOR_VISUAL_H__

#ifndef __ACTOR_VISUAL_H__
#define __ACTOR_VISUAL_H__

#include <foenix/vicky.h>
#include "coordinate.h"
#include "list.h"

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

// The order used here is intended to matter, higher numbers should
// be displayed above those with lower number.
enum actor_kind {
  Aerodrome,
  Artillery,
  LightArchie,
  MediumArchie,
  HeavyArchie,
  Infanrty,
  Cavalry,
  MachineGun,
  Ballon,       // Obseravtion ballon
  FlamingOnion, // Concentration of such
  DogFight,     // An active dogfight
  Flight,
};

// We do not really need the entire sprite record as most things
// can be deduced.
struct sprite_info {
  uint16_t control[2];
  uint16_t addy[2];
};

struct actor_visual {
  // Actors are sorted on y position and when occupying the same position
  // based on the kind/order of the node.
  // The 'node.kind' is also used to point back to the owning rich record.
  struct typed_node node; // sorted on coordinate / show_y
  uint16_t show_x;        // position for this frame
  uint16_t show_y;
  uint16_t staggered;     // used to adjust x/y when placed on top
  struct sprite_info sprite_info; // actual sprite data to be used
  unsigned sprite_index;   // the physical sprite (index) assigned to
  uint16_t x;           // position is updated here
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

extern void add_visual(struct list *visual, struct actor_visual *, location, struct sprite_info *);
extern void add_visual_xy(struct list *visual, struct actor_visual *, uint16_t x, uint16_t y, struct sprite_info *);
extern void install_interrupt_handlers(void);
extern void restore_interrupt_handlers(void);

#endif // __ACTOR_VISUAL_H__

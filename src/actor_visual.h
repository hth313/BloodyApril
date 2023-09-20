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

struct actor_visual {
  struct node node;     // sorted on show_y
  uint16_t show_x;      // position for this frame
  uint16_t show_y;
  struct sprite sprite; // actual sprite data to be used
  unsigned sprite_index;
  uint16_t x;           // position is updated here
  uint16_t y;
  // Pointer to rich data record
  enum actor_kind actor_kind;
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

extern void add_visual(struct list *visual, struct actor_visual *, location, struct sprite *);
extern void add_visual_xy(struct list *visual, struct actor_visual *, uint16_t x, uint16_t y, struct sprite *);
extern void install_interrupt_handlers(void);
extern void restore_interrupt_handlers(void);

#endif // __ACTOR_VISUAL_H__

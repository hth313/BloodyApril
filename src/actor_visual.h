#ifndef __ACTOR_VISUAL_H__
#define __ACTOR_VISUAL_H__

#include <foenix/sprite.h>
#include "actor.h"
#include "dogfight.h"
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

extern void init_visual(struct actor_visual *, location *, struct sprite *);


#endif // __ACTOR_VISUAL_H__

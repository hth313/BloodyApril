#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "altitude.h"
#include "coordinate.h"
#include "list.h"
#include "hashmap.h"

enum actor_kind {
  Ballon,       // Obseravtion ballon
  FlamingOnion, // Concentration of such
  DogFight,     // An active dogfight
  Artillery,
  LightArchie,
  MediumArchie,
  HeavyArchie,
  Infanrty,
  Cavalry,
  MachineGun,
  Flight,
  Aerodrome,
};

// Ballons are mainly for observation. They can be targets to down in scenarios.
struct ballon {
  struct typed_node node;
  enum altitude_band altitude;
};

// Actors in the same sector, this does not include flights that are moving.
struct actors_pos {
  coordinate pos;
  struct list actors;
};

// Actors are hashed based on their coordinate.
typedef struct hashmap actorsmap;

// **********************************************************************

// Add an actor at a given sector. The list of all actors in this sector
// is returned and can be inspected to see if there are something that
// prevented it from happening, in that case the caller can unlink it again.
extern struct list *add_actor(actorsmap *map, coordinate pos,
                              struct typed_node *node);
extern void unlink_actor(actorsmap *map, coordinate pos,
			 struct typed_node *node);
#endif // __ACTOR_H__

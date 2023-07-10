#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "coordinate.h"
#include "list.h"

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
};

// Ballons are mainly for observation. They can be targets to down in scenarios.
struct ballon {
  struct node_kind node;
  enum altitude_band altitude;
};

// Actors in the same sector, this does not include flights that are moving.
struct actors {
  coordinate pos;
  struct list actors;
};

// Actors are hashed based on their coordinate.
typedef struct hashmap all_actors;


// **********************************************************************

// Add an actor at a given sector. The list of all actors in this sector
// is returned and can be inspected to see if there are something that
// prevented it from happening, in that case the caller can unlink it again.
extern struct list *add_actor(all_actors *map, coordinate pos, struct node_kind *node);

#endif // __ACTOR_H__

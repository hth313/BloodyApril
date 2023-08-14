#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "actor_visual.h"
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
  struct actor_visual visual;
  enum altitude_band altitude;
  bool allied;
};

struct flaming_onion {
  struct typed_node node;
  struct actor_visual visual;
  bool allied;
};

struct artillery {
  struct typed_node node;
  bool allied;
  struct actor_visual visual;
};

struct archie {
  struct typed_node node;
  struct actor_visual visual;
  bool allied;
  uint16_t strength;
};

struct infantry {
  struct typed_node node;
  struct actor_visual visual;
  bool allied;
  uint16_t strength;
};

struct cavalry; {
  struct typed_node node;
  struct actor_visual visual;
  bool allied;
  uint16_t strength;
};

struct machine_gun {
  struct typed_node node;
  struct actor_visual visual;
  bool allied;
  uint16_t strength;
};

// Actors in the same sector, this does not include flights that are moving.
struct actors_pos {
  coordinate pos;
  struct list actors;
};

// Actors are hashed based on their coordinate.
typedef struct hashmap *actorsmap;

// **********************************************************************

extern actorsmap new_actorsmap(void);
extern void new_ballon(coordinate pos, enum altitude_band altitude, bool allied);
extern void new_flaming_onion(coordinate pos, bool allied);
extern void new_artillery(coordinate pos, bool allied);
extern void new_cavalry(coordinate pos, bool allied);
extern void new_infantry(coordinate pos, bool allied);
extern void new_machine_gun(coordinate pos, bool allied);
extern void new_archie(coordinate pos, uint16_t strength, bool allied);

// Add an actor at a given sector. The list of all actors in this sector
// is returned and can be inspected to see if there are something that
// prevented it from happening, in that case the caller can unlink it again.
extern struct list *add_actor(actorsmap map, coordinate pos,
                              struct typed_node *node);
extern void unlink_actor(actorsmap map, coordinate pos,
			 struct typed_node *node);
#endif // __ACTOR_H__

#ifndef __DOGFIGHT_H__
#define __DOGFIGHT_H__

#include <stdbool.h>
#include "actor.h"
#include "airplane.h"
#include "list.h"

struct playstate;

// A dogfight is a separation of a fight between airplanes that takes
// a maximum number of turns. Airplanes are separated and engage each
// others until the maxim=um turns are up or some other ending
// criteria occurs.
struct dogfight {
  struct typed_node node;
  struct list allied_powers;
  struct list central_powers;
  bool allied_attacker;
  // ^ True if allied side is seen as attacker in dogfight.
  // The "attacker" role can be either side an may switch during
  // a dogfight.
  unsigned round;            // counter
  bool attacker_disengage;   // overall order
  bool defender_disengage;   // overall order
};

// **********************************************************************

extern bool dogfight(struct dogfight *df);
extern struct dogfight *new_dogfight(struct list *allied_powers,
                                     struct list *central_powers,
                                     bool allied_attacker);
extern void drop_dogfight(struct playstate*, struct dogfight*);
#endif // __DOGFIGHT_H__

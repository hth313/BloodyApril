#include <stdlib.h>
#include "actor."
#include "ai.h"
#include "airplane.h"
#include "altitude.h"
#include "combat.h"
#include "dogfight.h"
#include "flight.h"
#include "list.h"
#include "playstate.h"
#include "ui.h"

// Allocate a new dogfight dynamically. The caller should link the created
// node into actors of the sector it occurs in.
struct dogfight *new_dogfight(struct list *allied_powers, struct list *central_powers,
                              bool allied_attacker) {
  struct dogfight *p = safe_malloc(sizeof(struct dogfight));
  p = {
      .allied_powers = allied,
      .central_powers = central_powers,
      .allied_attacker = allied_attacker,
      .round = 0,
  };
  init_visual(&p->visual, position, sprite);
  p->visual.actor_kind = DogFight;
  p->visual.dogfight = p;

  return p;
}

// Downed flights are moved to downed list, the flight is moved to the
// play state, if flight became empty it is dropped.
static void move_downed(struct playstate *ps, struct list *flights) {
  struct flight *flight;
  struct flight *next;
  foreach_node_safe(flights, flight, next) {
    if (!prune_downed(ps, flight)) {
      order_insert(&ps->flights, &flight->node);
    }
  }
}

void drop_dogfight(struct playstate *ps, struct dogfight *df) {
  move_downed(ps, &df->allied_powers);
  move_downed(ps, &df->central_powers);
  unlink_actor(&ps->actors, df->pos, df);
  free(df);
}

static void dogfight_reset_orders(struct dogfight *df) {
  df->attacker_disengage = false;
  df->defender_disengage = false;
}

static bool attempt_disengage(struct list *disengagers,
                              struct list *opponents) {
  // Find slowest airplane
  struct speeds disengagers_airspeeds = slowest_speed(disengagers);
  struct speeds opponents_airspeeds = slowest_speed(opponents);
  if (disengagers_airspeeds.slowest > opponents_airspeeds.fastest) {
    return true;
  }
  return (disengagers_airspeeds.escape_score + (rand() % 10) >
          opponents_airspeeds.escape_score + (rand() % 10));
}

// Handle a single round in a dogfight.
bool dogfight(struct dogfight *df) {
  // 1. Draw the screen for the dogfight, for this round.
  draw_dogfight(df);

  // 2. Input orders for the next round.
  dogfight_reset_orders(df);
  if (df->allied_attacker) {
    ai_dogfight_orders(df);
    user_dogfight_orders(df);
  } else {
    user_dogfight_orders(df);
    ai_dogfight_orders(df);
  }

  // 3. Disengage if both sides wants to disengage
  if (df->attacker_disengage && df->defender_disengage) {
    return false;
  }

  bool allied_disengage =
       (df->attacker_disengage &&  df->allied_attacker)
    || (df->defender_disengage && !df->allied_attacker);
  bool central_disengage =
       (df->attacker_disengage && !df->allied_attacker)
    || (df->defender_disengage &&  df->allied_attacker);

  // 4. Only defender wants to disengage, check if successful
  if (df->defender_disengage) {
    if (allied_disengage &&
        attempt_disengage(&df->allied_powers, &df->central_powers)) {
      return false;
    }
    if (central_disengage &&
	attempt_disengage(&df->central_powers, &df->allied_powers)) {
      return false;
    }
  }

  // 5. If attacker (only) attempts to disengange and defender did not
  // declare disengange, the roles are reversed.
  if (df->attacker_disengage && !df->defender_disengage) {
    df->allied_attacker = !df->allied_attacker;
  }

  struct list *attackers;
  struct list *defenders;
  bool defenders_disengage;
  if (df->allied_attacker) {
    attackers = &df->allied_powers;
    defenders = &df->central_powers;
    defenders_disengage = central_disengage;
  } else {
    attackers = &df->central_powers;
    defenders = &df->allied_powers;
    defenders_disengage = allied_disengage;
  }

  // 6. Resolve actual combat for this round.
  resolve_combat(attackers, defenders, defenders_disengage);

  // 7. If all attackers are damaged, the dogfight is over.
  bool all_damaged = true;
  for (airplane *p = (airplane*) attackers->head;
       p->node.succ != 0;
       p = (airplane*) p->node.succ) {
    if (!damaged(p)) {
      all_damaged = false;
      break;
    }
  }
  if (all_damaged) {
    return false;  // all damaged, so it is over
  }

  // 8. Increment round counter, if we hit the limit the dogfight is over.
  df->round++;
  return df->round < 11;  // return true if dogfight is still active
}

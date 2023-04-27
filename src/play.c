#include "combat.h"
#include "dogfight.h"

static void dogfight_reset_orders (dogfight *df) {
  df->attacker_disengage = false;
  df->defender_disengage = false;
}

// Handle a single round in a dogfight.
bool dogfight(dogfight *df) {
  // 1. Draw the screen for the dogfight, for this round.
  draw_dogfight(df);

  // 2. Input orders for the next round.
  dogfight_reset_orders(df);
  if (df->side0_attacker) {
    ai_dogfight_orders(df);
    dogfight_orders(df);
  } else {
    dogfight_orders(df);
    ai_dogfight_orders(df);
  }

  // 3. Disengage if both sides wants to disengage
  if (df->attacker_disengage && df->defender_disengage) {
    return false;
  }

  // 4. Only defender wants to disengage, check if successful
  if (df->defender_disengage) {


  }

  // 5. If attacker (only) attempts to disengange and defender did not
  // declare disengange, the roles are reversed.
  if (df->attacker_disengage && !df->defender_disengage) {
    df->side0_attacker = !df->side0_attacker;
  }

  struct list *attacker;
  struct list *defender;
  if (df->allied_attacker) {
    attacker = &df->allied_powers;
    defender = &df->central_powers;
  } else {
    attacker = &df->central_powers;
    defender = &df->allied_powers;
  }

  // 6. Resolve actual combat for this round.
  resolve_combat(attacker, defender);

  // 7. If all attackers are damaged, the dogfight is over.
  bool all_damaged = true;
  for (airplane *p = (airplane*) attacker->node.head;
       p->node.succ != 0;
       p = (airplane*) = p->node.succ) {
    if (!damaged((p)) {
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

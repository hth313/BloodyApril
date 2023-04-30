#include <stdlib.h>
#include "airplane.h"
#include "pilot.h"
#include "weather.h"

static unsigned int prepare(struct list* list) {
  int count;
  for (airplane *p = (airplane*) list->head;
       p->node.succ != 0;
       p = (airplane*) p->node.succ) {
    p->added_property = 0;
    count++;
  }
  return count;
}

static void update_damage(struct list* list) {
  int count;
  for (airplane *p = (airplane*) list->head;
       p->node.succ != 0;
       p = (airplane*) p->node.succ) {
    p->property |= p->added_property;
  }
}

static bool has_active_attack_gun(airplane *p) {
  if (p->rounds_left) {
    uint16_t base_property = airplane_data[p->airplane]->property;
    if (  (base_property & AIRPLANE_FRONT_GUN)
        && (p->property & AIRPLANE_FRONT_GUN_JAMMED) == 0) {
      return true;
    } else if (  (base_property & AIRPLANE_FRONT_GUNx2)
               && (p->property & AIRPLANE_FRONT_GUNx2_JAMMED) == 0) {
      return true;
    }
  }
  return false;
}

static bool has_active_defense_gun(airplane *p) {
  return has_active_attack_gun(p);
}

static bool altitude_in_range(airplane *attacker, airplane *defender) {
  if (defender->altitude > attacker->altitude) {
    return false;
  }
  enum altitude_band attacker_band = altitude_band(attacker->altitude);
  enum altitude_band defender_band = altitude_band(defender->altitude);
  if (attacker_band == defender_band || attacker_band - 1 == defender_band) {
    // Height in range, check for clouds
    if (   global_weather.cloud_altitude == attacker_band
        && global_weather.cloud_altitude == defender_band) {
      if (global_weather.cloud_intensity < 20) {
        return true;
      }
      if ((rand() & 255) < global_weather.cloud_intensity * 3) {
        return true;
      }
    }
  }
  return false;
}

static void combat(airplane *attacker, struct list *defender, int defenders) {
  airplane* target[defenders + 1];
  unsigned i = 0;

  // Determine possible opponents.
  for (airplane *p = (airplane*) defender->head;
       p->node.succ != 0;
       p = (airplane*) p->node.succ) {
    if ((p->property & CAN_BE_ATTACKED_MASK) == 0
        && altitude_in_range(attacker, p)) {
      target[i] = p;
      i++;
    }
  }

  if (i > 0) {
    // Determine shot opportunities
    unsigned base_maneuver_chance = 50;
    unsigned chances = umax(4, i);

    struct pilot *attacker_pilot = pilot_data[attacker->pilot];
    struct airplane_kind *attacker_kind = airplane_data[attacker->airplane];

    while (chances > 0 && attacker->rounds_left && (attacker->added_property & GUN_MASK) == 0) {
      // Maneuver for an opponent
      struct airplane *defender = target[rand() % i];
      struct pilot *defender_pilot = pilot_data[defender->pilot];
      struct airplane_kind *defender_kind = airplane_data[defender->airplane];
      unsigned maneuver_chance = base_maneuver_chance
        + (defender_pilot->strength - attacker_pilot->strength) * 4
        + (attacker_kind->agility - defender_kind->agility) * 2;
      if (maneuver_chance > rand()) {
        // In position, fire round and call it (1-8) * 4, this
        // simulates how good the opportunity was, this can cut out 1/3 of
        // the total ammo. Capped with remaining shots.
        unsigned rounds = umax(((rand() & 7) + 1) * 4, attacker->rounds_left);
        unsigned mask = 15;
        if ((rand() % 35) > rounds) {
          if (rounds > 20) {
            if ((rand() & 0x100) || (defender->added_property & AIRPLANE_CRIPPLED)) {
              defender->added_property |= AIRPLANE_DOWNED;
            } else {
              // Long round, more aggressive damage
              mask = 7;
            }
            switch (rand() & mask) {
            case 0:
              defender->added_property |= AIRPLANE_ENGINE_FAILURE;
            case 1:
            case 2:
              defender->added_property |= AIRPLANE_SPIN;
            default:
              defender->added_property |= AIRPLANE_CRIPPLED;
            }
          }
        }
        // Now see if gun jammed.
        switch (rand() & mask) {
        case 0:
        case 1:
          if (((attacker->property | attacker->added_property) & AIRPLANE_FRONT_GUN_JAMMED)) {
            attacker->added_property |= AIRPLANE_FRONT_GUNx2_JAMMED;
          } else {
            attacker->added_property |= AIRPLANE_FRONT_GUN_JAMMED;
          }
          break;
        default:
          break;
        }
        attacker->rounds_left -= rounds;
      }
      chances--;
      base_maneuver_chance /= 2;
    }
  }
}

void resolve_combat(struct list *attacker, struct list *defender,
		    bool defenders_attempted_disengage) {
  // 1. Prepare for fight.
  unsigned int attackers = prepare(attacker);
  unsigned int defenders = prepare(defender);

  // 2. Traverse attackers, randomly try to engage a defender.
  for (airplane *p = (airplane*) attacker->head;
       p->node.succ != 0;
       p = (airplane*) p->node.succ) {
    // Can this one attack?
    if (   (p->property & OUT_MASK) == 0
        && has_active_attack_gun(p)) {
      combat(p, defender, defenders);
    }
  }

  // 3. Traverse defenders, randomly try to engage an attacker.
  //    Defenders only attack if they did not try to get away.
  if (!defenders_attempted_disengage) {
    for (airplane *p = (airplane*) defender->head;
	 p->node.succ != 0;
	 p = (airplane*) p->node.succ) {
      // Can this one attack?
      if (   (p->property & OUT_MASK) == 0
	     && has_active_defense_gun(p)) {
	combat(p, attacker, attackers);
      }
    }
  }

  update_damage(attacker);
  update_damage(defender);

}

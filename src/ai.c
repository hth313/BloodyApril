#include "airplane.h"
#include "ai.h"
#include "list.h"

struct speeds slowest_speed(struct list *list) {
  unsigned slowest = 1000;
  unsigned fastest = 0;
  unsigned count = 0;
  unsigned escape_score = 0;
  for (airplane *p = list->head; p->node.succ != 0;
       p = (airplane *)p->node.succ) {
    if (!p->damaged) {
      struct airplane_kind *kind = airplane_data[p->airplane];
      escape_score += kind->agility + kind->aggression;
      unsigned speed = kind->speed[altitude_band(p->altitude)];
      if (speed < slowest) {
	slowest = speed;
      }
      if (speed > fastest) {
	fastest = speed;
      }
      count++;
    }
  }
  if (count > 0) {
    escape_score = count + escape_score / count;
  }

  return (struct speeds) { slowest, fastest, escape_score };
}

void ai_dogfight_orders(struct dogfight *df) {
  struct speeds allied_airspeeds = slowest_speed(&df->allied_powers);
  struct speeds central_airspeeds = slowest_speed(&df->central_powers);

  if (df->allied_attacker) {
    if (allied_airspeeds.escape_score > central_airspeeds.escape_score + 5 &&
        (rand() & 1)) {
      // Allied attacker and quite a bit stronger, give 50% chance that we bail.
      df->defender_disengage = true;
    } else if (allied_airspeeds.escape_score > central_airspeeds.escape_score
	       && (rand() & 15) < 2) {
      // Allied attacker and slightly stronger, just maybe bail
      df->defender_disengage = true;
    }
  } else {
    unsigned limit df->defender_disengage ? 10 : 5;
    if (allied_airspeeds.escape_score > central_airspeeds.escape_score + limit &&
	(rand() & 1)) {
      df->attacker_disengage = true;
    }
  }
}

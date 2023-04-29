#ifndef __AI_H__
#define __AI_H__

#include "dogfight.h"

struct speeds {
  unsigned slowest;
  unsigned fastest;
  unsigned escape_score;
};

extern struct speeds slowest_speed(struct list *list);
extern void ai_dogfight_orders(struct dogfight*);

#endif // __AI_H__

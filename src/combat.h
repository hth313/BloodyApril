#ifndef __COMBAT_H__
#define __COMBAT_H__

#include "list.h"

extern void resolve_combat(struct list *attacker, struct list *defender,
                           bool defenders_attempted_disengage);

#endif // __COMBAT_H__

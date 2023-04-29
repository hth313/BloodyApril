#ifndef __UI_H__
#define __UI_H__

#include "dogfight.h"

enum cursor_position {
  CommandPosition
};

// API
extern void cursor_to(enum cursor_position);
extern void draw_dogfight(struct dogfight*);

extern void user_dogfight_orders(struct dogfight*);

// Support
extern void show_airunit(airplane *p, bool allied);

#endif // __UI_H__

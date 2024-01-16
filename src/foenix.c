#include "airplane.h"
#include "dogfight.h"
#include "ui.h"

#ifdef __CALYPSI_TARGET_SYSTEM_FOENIX__
#include <foenix/vicky.h>
#ifdef __CALYPSI_TARGET_M68K__
#include <mcp/syscalls.h>
#endif
#endif

#define Screen 0

// Offset player sprites a little to have sprites that can be on top of them.
#define AirplaneSpriteOffset 10

#define SpriteControlAirplane 1

static unsigned sprite_index(struct airplane_kind *k) {
  return AirplaneSpriteOffset + k->token;
}

void cursor_to(enum cursor_position to) {
  switch (to) {
  case CommandPosition:
#ifdef __CALYPSI_TARGET_M68K__
    sys_txt_set_xy(Screen, 20, 0);
#endif
    break;
  }
}

static void draw_airplane_column(struct list *list, unsigned column) {
  int row = 0;

  for (airplane *p = (airplane *)list->head; p->node.succ != 0;
       p = (airplane *)p->node.succ) {
    struct airplane_kind const *k = airplane_kind(p);
    volatile struct sprite *sprite = &Sprite[p->sprite_index];
    sprite->x = 50;
    sprite->y = 50 + row * 20;
    sprite->control = p->visual.sprite[0].control;
#ifdef __CALYPSI_TARGET_M68K__
    sprite->addy_high = p->visual.sprite[0].addy_high;
    sys_txt_set_xy(Screen, row, column);
#else
    sprite->data = p->visual.sprite[0].data;
#endif
    show_airunit(p, column < 40);
    row++;
  }
}

void draw_dogfight(struct dogfight* df) {
  draw_airplane_column(&df->allied_powers, 0);
  draw_airplane_column(&df->central_powers, 40);
}

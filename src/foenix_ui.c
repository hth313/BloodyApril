#include "airplane.h"
#include "dogfight.h"
#include "ui.h"

#ifdef __CALYPSI_TARGET_SYSTEM_A2560U__
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

static int draw_airplane_column(int sprite_index, struct list *list, unsigned column) {
  int row = 0;

  for (airplane *p = (airplane *)list->head; p->node.succ != 0;
       p = (airplane *)p->node.succ) {
    volatile VRAM struct sprite *sprite = &Sprite[sprite_index];
    *sprite = *p->actor_tile;
    sprite->x = 50;
    sprite->y = 50 + row * 20;
    sprite->control = p->visual.actor_tile.control;
#ifdef __CALYPSI_TARGET_M68K__
    sprite->addy_high = p->visual.actor_tile.addy_high;
    sys_txt_set_xy(Screen, row, column);
#else
    sprite->data = p->visual.sprite[0].data;
#endif
    show_airunit(p, column < 40);
    row++;
    sprite_index++;
  }
  return sprite_index;
}

void draw_dogfight(struct dogfight* df) {
  int index  = draw_airplane_column(0, &df->allied_powers, 0);
  draw_airplane_column(index, &df->central_powers, 40);
}

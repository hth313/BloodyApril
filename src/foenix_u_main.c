#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <foenix/vicky.h>
#include "color.h"
#include "playstate.h"
#include "random.h"
#include "scenario.h"
#include "system.h"

extern sprite_t Albatros_D2_sprite;
extern sprite_t Albatros_D5a_J3_sprite;
extern VRAM uint16_t trench1_index[];
extern VRAM uint8_t  trench1_tiles[];

extern __far lut_t palette;

static unsigned values[20];
static unsigned control1, control2;

static inline void set_sprite(int index, struct sprite *sprite, uint16_t x, uint16_t y) {
  uint16_t *p = (uint16_t*) &Sprite[index];
  *p++ = sprite->control;
  *p++ = sprite->addy_high;
  *p++ = x;
  *p = y;
#if 0
  Sprite[0].control = sprite->control;
  Sprite[0].addy_high = sprite->addy_high;
  Sprite[0].x = x;
  Sprite[0].y = y;
#endif
}

int main() {
  init_seed();

  control1 = Vicky.master_control;
  Vicky.master_control = GRAPHIC_MODE_ENABLE | SPRITE_ENGINE_ENABLE | TILE_ENGINE_ENABLE; //  | TEXT_MODE_ENABLE;
//    | BITMAP_ENGINE_ENABLE;
  control2 = Vicky.master_control;

//  LUT[0] = palette;
//  LUT[1] = palette;
//  memcpy(&LUT[0], &palette, 200);

  Vicky.background_color = BACKGROUND_COLOR;
  Vicky.border_color = BORDER_COLOR;


#if 0
  for (unsigned i = 0; i < 20; i++) {
    values[i] = roll2d10();
  }
#endif

  Tilemap[3].control = 1; // enable layer
  Tilemap[3].data = vicky_address((vram_ptr)trench1_index);
  Tilemap[3].width = 112;
  Tilemap[3].height = 64;
  Tilemap[3].x = 0;
  Tilemap[3].y = 0;

  Tileset[0].tileset_register = (uint32_t) vicky_address((vram_ptr)trench1_tiles);

  set_sprite(0, &Albatros_D2_sprite, 100, 100);
//  Sprite[0] = Albatros_D2_sprite;
#if 0
  Sprite[0].control = SPRITE_ENABLE | SPRITE_LUT(1)
    | SPRITE_ADDY_LOW(vicky_address(Albatros_D2_sprite));
  Sprite[0].addy_high = SPRITE_ADDY_HIGH(vicky_address(Albatros_D2_sprite));
#endif
//  Sprite[0].x = 100;
//  Sprite[0].y = 100;

  set_sprite(1, &Albatros_D5a_J3_sprite, 150, 150);
//  Sprite[1] = Albatros_D5a_J3_sprite;
#if 0
  Sprite[1].control = SPRITE_ENABLE | SPRITE_LUT(1)
    | SPRITE_ADDY_LOW(vicky_address(Albatros_D5a_J3_sprite));
  Sprite[1].addy_high = SPRITE_ADDY_HIGH(vicky_address(Albatros_D5a_J3_sprite));
#endif
//  Sprite[1].x = 120;
//  Sprite[1].y = 150;

  struct scenarios *scenarios = initialize_scenarios();
  struct playstate *playstate = new_playstate();

  // For now, play with the first scenario
  playstate->scenario = (struct scenario*) scenarios->trainer_scenarios.head;
  playstate->scenario->setup(playstate);
  playstate->scenario->playturn(playstate);
  playstate->scenario->summarize(playstate);

  while (1) {
    static int xx;
    static char last_char;
    xx = values[5];
    if (fread(&last_char, 1, 1, stdin) == 1) {
      // got a char.
      int dice = roll2d10();
    }
  }
}

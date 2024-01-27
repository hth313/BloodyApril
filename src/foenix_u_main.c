#include <stdint.h>
#include <string.h>
#include <foenix/vicky.h>
#include "random.h"

extern VRAM sprite_t Albatros_D2_sprite;
extern VRAM sprite_t Albatros_D5a_J3_sprite;
extern VRAM uint16_t trench1_index[];
extern VRAM uint8_t  trench1_tiles[];

//extern __far lut_t palette;

static unsigned values[20];
static unsigned control1, control2;

int main() {
  init_seed();

  control1 = Vicky.master_control;
  Vicky.master_control = GRAPHIC_MODE_ENABLE | SPRITE_ENGINE_ENABLE | TILE_ENGINE_ENABLE; //  | TEXT_MODE_ENABLE;
//    | BITMAP_ENGINE_ENABLE;
  control2 = Vicky.master_control;

//  LUT[1] = palette;
//  memcpy(&LUT[0], &palette, 200);

  Vicky.background_color = (color24_t) { 0xc6, 0xe6, 0xec };
  Vicky.border_color = (color24_t) { 0, 0, 0 };


  for (unsigned i = 0; i < 20; i++) {
    values[i] = roll2d10();
  }

  Tilemap[3].control = 1; // enable layer
  Tilemap[3].data = vicky_address((vram_ptr)trench1_index);
  Tilemap[3].width = 112;
  Tilemap[3].height = 64;
  Tilemap[3].x = 640;
  Tilemap[3].y = 0;

#ifdef __CALYPSI_TARGET_M68K__
  Tileset[0].tileset_register = (uint32_t) vicky_address((vram_ptr)trench1_tiles);
#else
  Tileset[0].data = vicky_address((vram_ptr)trench1_tiles);
#endif

  Sprite[0] = Albatros_D2_sprite;
#if 0
  Sprite[0].control = SPRITE_ENABLE | SPRITE_LUT(1)
    | SPRITE_ADDY_LOW(vicky_address(Albatros_D2_sprite));
  Sprite[0].addy_high = SPRITE_ADDY_HIGH(vicky_address(Albatros_D2_sprite));
#endif
  Sprite[0].x = 100;
  Sprite[0].y = 100;

  Sprite[1] = Albatros_D5a_J3_sprite;
#if 0
  Sprite[1].control = SPRITE_ENABLE | SPRITE_LUT(1)
    | SPRITE_ADDY_LOW(vicky_address(Albatros_D5a_J3_sprite));
  Sprite[1].addy_high = SPRITE_ADDY_HIGH(vicky_address(Albatros_D5a_J3_sprite));
#endif
  Sprite[1].x = 120;
  Sprite[1].y = 150;

  while (1) {
    static int xx;
    xx = values[5];
  }
}

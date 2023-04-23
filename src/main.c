#include <string.h>
#include <foenix/vicky.h>
extern __far uint8_t alboatros_II[SPRITE_SIZE];
extern __far lut_t palette;


void main () {
  Vicky.master_control = GRAPHIC_MODE_ENABLE | SPRITE_ENGINE_ENABLE
    | BITMAP_ENGINE_ENABLE | GAMMA_ENABLE;

//  memcpy(&LUT[1], &palette, 200);

  Sprite[0].control = SPRITE_ENABLE | SPRITE_LUT(1)
    | SPRITE_ADDY_LOW(vicky_address(alboatros_II));
  Sprite[0].addy_high = SPRITE_ADDY_HIGH(vicky_address(alboatros_II));
  Sprite[0].x = 100;
  Sprite[0].y = 100;

  Sprite[1].control = SPRITE_ENABLE | SPRITE_LUT(1)
    | SPRITE_ADDY_LOW(vicky_address(alboatros_II));
  Sprite[1].addy_high = SPRITE_ADDY_HIGH(vicky_address(alboatros_II));
  Sprite[1].x = 150;
  Sprite[1].y = 150;

  while (1);
}

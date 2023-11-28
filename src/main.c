#include <stdint.h>
#include <string.h>
#include <foenix/vicky.h>
extern __far uint8_t Albatros_D2_sprite[SPRITE_SIZE];
extern __far uint8_t Albatros_D5a_J3_sprite[SPRITE_SIZE];
extern __far lut_t palette;

void main () {
  Vicky.master_control = GRAPHIC_MODE_ENABLE | SPRITE_ENGINE_ENABLE
    | BITMAP_ENGINE_ENABLE | GAMMA_ENABLE;

//  memcpy(&LUT[1], &palette, 200);

  Sprite[0].control = SPRITE_ENABLE | SPRITE_LUT(1)
    | SPRITE_ADDY_LOW(vicky_address(Albatros_D2_sprite));
  Sprite[0].addy_high = SPRITE_ADDY_HIGH(vicky_address(Albatros_D2_sprite));
  Sprite[0].x = 100;
  Sprite[0].y = 100;

  Sprite[1].control = SPRITE_ENABLE | SPRITE_LUT(1)
    | SPRITE_ADDY_LOW(vicky_address(Albatros_D5a_J3_sprite));
  Sprite[1].addy_high = SPRITE_ADDY_HIGH(vicky_address(Albatros_D5a_J3_sprite));
  Sprite[1].x = 150;
  Sprite[1].y = 150;

  while (1);
}

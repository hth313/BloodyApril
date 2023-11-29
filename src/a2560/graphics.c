#include <foenix/vicky.h>
#include <stdbool.h>

extern uint8_t right_facing_dogfight_sprite_data[SPRITE_SIZE];
extern uint8_t left_facing_dogfight_sprite_data[SPRITE_SIZE];

struct sprite right_facing_dogfight_sprite;

struct sprite left_facing_dogfight_sprite;


void initialize() {
  Vicky.master_control =
      GRAPHIC_MODE_ENABLE | TILE_ENGINE_ENABLE | SPRITE_ENGINE_ENABLE;

  right_facing_dogfight_sprite = (struct sprite){
    .enable = true, .lut = 0, .depth = 1, .collision_enable = false,
    .addy_low = SPRITE_ADDY_LOW(right_facing_dogfight_sprite_data),
    .addy_high = SPRITE_ADDY_HIGH(right_facing_dogfight_sprite_data)
  };

  left_facing_dogfight_sprite = (struct sprite){
    .enable = true, .lut = 0, .depth = 1, .collision_enable = false,
    .addy_low = SPRITE_ADDY_LOW(left_facing_dogfight_sprite_data),
    .addy_high = SPRITE_ADDY_HIGH(left_facing_dogfight_sprite_data)
  };

}

void initialize_tilemap(vram_ptr tile_map[4], vram_ptr tile_graphics[4]) {
  for (unsigned i = 0; i < 4; i++) {
    Tilemap[i].data = tile_map[i];
    Tilemap[i].layer_enable = 1;
    Tilemap[i].width = 112;
    Tilemap[i].height = 64;
    Tileset[i].addy = tile_graphics[i];
  }
}

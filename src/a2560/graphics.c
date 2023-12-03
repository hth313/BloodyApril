#include <foenix/vicky.h>
#include <stdbool.h>

void initialize() {
  Vicky.master_control =
      GRAPHIC_MODE_ENABLE | TILE_ENGINE_ENABLE | SPRITE_ENGINE_ENABLE;

}

void initialize_tilemap(vram_ptr tile_map[4], vram_ptr tile_graphics[4]) {
  for (unsigned i = 0; i < 4; i++) {
    Tilemap[i].data = tile_map[i];
    Tilemap[i].layer_enable = 1;
    Tilemap[i].width = 112;
    Tilemap[i].height = 64;
#ifdef __CALYPSI_TARGET_M68K__
    Tileset[i].addy = (volatile uint32_t) vicky_address(tile_graphics[i]);
#else
    Tileset[i].data = vicky_address(tile_graphics[i]);
#endif
  }
}

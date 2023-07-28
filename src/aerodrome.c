#include "aerodrome.h"
#include "actor_sprite.h"
#include "coordinate.h"
#include <stdbool.h>
#include <foenix/vicky.h>

extern uint8_t allied_aerodrome_sprite_data[SPRITE_SIZE];
extern uint8_t central_aerodrome_sprite_data[SPRITE_SIZE];

struct aerodrome Provin;
struct aerodrome Proville;

struct sprite allied_aerodrome;
struct sprite central_aerodrome;

static void initialize(struct aerodrome *aerodrome, char *name, bool allied, coordinate pos) {
  aerodrome->name = name;
  aerodrome->pos = pos;
  init_list(&aerodrome->fights);
  init_list(&aerodrome->airplanes);
  init_list(&aerodrome->squadron);
  init_visual(&aerodrome->visual, pos, allied ? &allied_aerodrome : central_aerodrome);
}

void create_aerodromes() {
  allied_aerodrome = {
    .enable = true,
    .lut = 0,
    .depth = 1,
    .collision_enable = false,
    .addy_low = SPRITE_ADDY_LOW(&allied_aerodrome_sprite_data);
    .addy_high = SPRITE_ADDY_HIGH(&allied_aerodrome_sprite_data);
  };
  central_aerodrome = {
    .enable = true,
    .lut = 0,
    .depth = 1,
    .collision_enable = false,
    .addy_low = SPRITE_ADDY_LOW(&central_aerodrome_sprite_data);
    .addy_high = SPRITE_ADDY_HIGH(&central_aerodrome_sprite_data);
  };
  initialize(&Provin, "Provin", false);
  initialize(&Proville, "Proville", false);
}

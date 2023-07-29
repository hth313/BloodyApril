// -*- coding: iso-latin-1 -*-
#include "aerodrome.h"
#include "actor_sprite.h"
#include "coordinate.h"
#include <stdbool.h>
#include <foenix/vicky.h>

extern uint8_t allied_aerodrome_sprite_data[SPRITE_SIZE];
extern uint8_t central_aerodrome_sprite_data[SPRITE_SIZE];

struct aerodrome Provin;
struct aerodrome Proville;
struct aerodrome Pronville;
struct aerodrome Guesnain;
struct aerodrome Phalempin;
struct aerodrome Faumont;
struct aerodrome Bersee;
struct aerodrome Roucourt;
struct aerodrome Epinoy;
struct aerodrome Villers_au_Tetre;
struct aerodrome LaBrayelle;
struct aerodrome Gonnelieu;
struct aerodrome Boistrancourt;
struct aerodrome Eswars;
struct aerodrome Pont_a_Marcq;
struct aerodrome Cuincy;
struct aerodrome Cantin;
struct aerodrome Emerchicourt;
struct aerodrome Corbehem;
struct aerodrome Abacon;

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
  initialize(&Pronville, "Pronville", false);
  initialize(&Guesnain, "Guesnain", false);
  initialize(&Phalempin, "Phalempin", false);
  initialize(&Faumont, "Faumont", false);
  initialize(&Bersee, "Bersée", false);
  initialize(&Roucourt, "Roucourt", false);
  initialize(&Epinoy, "Épinoy", false);
  initialize(&Villers_au_Tetre, "Villers-au-Tetre", false);
  initialize(&LaBrayelle, "La Brayelle", false);
  initialize(&Gonnelieu, "Gonnelieu", false);
  initialize(&Boistrancourt, "Boistrancourt", false);
  initialize(&Eswars, "Eswars", false);
  initialize(&Pont_a_Marcq, "Pont-à-Marcq", false);
  initialize(&Cuincy, "Cuincy", false);
  initialize(&Cantin, "Cantin", false);
  initialize(&Emerchicourt, "Émerchicourt", false);
  initialize(&Corbehem, "Corbehem", false);
  initialize(&Abacon, "Abacon", false);
}

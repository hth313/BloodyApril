// -*- coding: iso-latin-1 -*-
#include "aerodrome.h"
#include "actor_sprite.h"
#include "coordinate.h"
#include <stdbool.h>
#include <foenix/vicky.h>

extern uint8_t allied_aerodrome_sprite_data[SPRITE_SIZE];
extern uint8_t central_aerodrome_sprite_data[SPRITE_SIZE];

struct aerodrome Abacon;
struct aerodrome Bersee;
struct aerodrome Boistrancourt;
struct aerodrome Cantin;
struct aerodrome Corbehem;
struct aerodrome Cuincy;
struct aerodrome Emerchicourt;
struct aerodrome Epinoy;
struct aerodrome Eswars;
struct aerodrome Faumont;
struct aerodrome Gonnelieu;
struct aerodrome Guesnain;
struct aerodrome LaBrayelle;
struct aerodrome Phalempin;
struct aerodrome Pont_a_Marcq;
struct aerodrome Pronville;
struct aerodrome Proville;
struct aerodrome Provin;
struct aerodrome Roucourt;
struct aerodrome Villers_au_Tetre;

struct aerodrome Auchel;
struct aerodrome Avesnes_le_Comte;
struct aerodrome Bellevue;
struct aerodrome Bruay;
struct aerodrome Chocques;
struct aerodrome Fienvillers;
struct aerodrome Fienvilliers;
struct aerodrome Filescamp;
struct aerodrome Hesdigneul;
struct aerodrome LeHameau;
struct aerodrome Lealvillers;
struct aerodrome Lozingham;
struct aerodrome Marieux;
struct aerodrome Savy;
struct aerodrome Soncamp;
struct aerodrome Treizennes;
struct aerodrome Vert_Galand;

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

  // Central power aerodromes
  initialize(&Abacon, "Abacon", false);
  initialize(&Bersee, "Bersée", false);
  initialize(&Boistrancourt, "Boistrancourt", false);
  initialize(&Cantin, "Cantin", false);
  initialize(&Corbehem, "Corbehem", false);
  initialize(&Cuincy, "Cuincy", false);
  initialize(&Emerchicourt, "Émerchicourt", false);
  initialize(&Epinoy, "Épinoy", false);
  initialize(&Eswars, "Eswars", false);
  initialize(&Faumont, "Faumont", false);
  initialize(&Gonnelieu, "Gonnelieu", false);
  initialize(&Guesnain, "Guesnain", false);
  initialize(&LaBrayelle, "La Brayelle", false);
  initialize(&Phalempin, "Phalempin", false);
  initialize(&Pont_a_Marcq, "Pont-à-Marcq", false);
  initialize(&Pronville, "Pronville", false);
  initialize(&Proville, "Proville", false);
  initialize(&Provin, "Provin", false);
  initialize(&Roucourt, "Roucourt", false);
  initialize(&Villers_au_Tetre, "Villers-au-Tetre", false);

  // Allied aerodromes
  initialize(&Auchel, "Auchel", true);
  initialize(&Avesnes_le_Comte, "Avesnes-le-Comte", true);
  initialize(&Bellevue, "Bellevue", true);
  initialize(&Bruay, "Bruay", true);
  initialize(&Chocques, "Chocques", true);
  initialize(&Fienvillers, "Fienvillers", true);
  initialize(&Fienvilliers, "Fienvilliers", true);
  initialize(&Filescamp, "Filescamp", true);
  initialize(&Hesdigneul, "Hesdigneul", true);
  initialize(&LeHameau, "Le Hameau", true);
  initialize(&Lealvillers, "Léalvillers", true);
  initialize(&Lozingham, "Lozingham", true);
  initialize(&Marieux, "Marieux", true);
  initialize(&Savy, Savy, true);
  initialize(&Soncamp, "Soncamp", true);
  initialize(&Treizennes, "Treizennes", true);
  initialize(&Vert_Galand, "Vert Galand", true);
}

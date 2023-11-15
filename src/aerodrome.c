// -*- coding: iso-latin-1 -*-
#include "aerodrome.h"
#include "actor_visual.h"
#include "coordinate.h"
#include "playstate.h"
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

static void initialize(struct aerodrome *aerodrome, char *name, bool allied,
                       coordinate pos) {
  aerodrome->name = name;
  aerodrome->pos = pos;
  init_list(&aerodrome->flights);
  init_list(&aerodrome->airplanes);
  init_list(&aerodrome->squadron);
  add_visual_coord(&aerodrome->visual, pos,
             allied ? &allied_aerodrome : &central_aerodrome);
  add_actor(pos, &aerodrome->visual);
}

void create_aerodromes() {
  allied_aerodrome = (struct sprite) {
    .enable = true,
    .lut = 0,
    .depth = 1,
    .collision_enable = false,
    .addy_low = SPRITE_ADDY_LOW(&allied_aerodrome_sprite_data),
    .addy_high = SPRITE_ADDY_HIGH(&allied_aerodrome_sprite_data)
  };
  central_aerodrome = (struct sprite) {
    .enable = true,
    .lut = 0,
    .depth = 1,
    .collision_enable = false,
    .addy_low = SPRITE_ADDY_LOW(&central_aerodrome_sprite_data),
    .addy_high = SPRITE_ADDY_HIGH(&central_aerodrome_sprite_data)
  };

  // Central power aerodromes
  initialize(&Abacon, "Abacon", false, (coordinate) {0});
  initialize(&Bersee, "Bersée", false, (coordinate) {0});
  initialize(&Boistrancourt, "Boistrancourt", false, (coordinate) {0});
  initialize(&Cantin, "Cantin", false, (coordinate) {0});
  initialize(&Corbehem, "Corbehem", false, (coordinate) {0});
  initialize(&Cuincy, "Cuincy", false, (coordinate) {0});
  initialize(&Emerchicourt, "Émerchicourt", false, (coordinate) {0});
  initialize(&Epinoy, "Épinoy", false, (coordinate) {0});
  initialize(&Eswars, "Eswars", false, (coordinate) {0});
  initialize(&Faumont, "Faumont", false, (coordinate) {0});
  initialize(&Gonnelieu, "Gonnelieu", false, (coordinate) {0});
  initialize(&Guesnain, "Guesnain", false, (coordinate) {0});
  initialize(&LaBrayelle, "La Brayelle", false, (coordinate) {0});
  initialize(&Phalempin, "Phalempin", false, (coordinate) {0});
  initialize(&Pont_a_Marcq, "Pont-à-Marcq", false, (coordinate) {0});
  initialize(&Pronville, "Pronville", false, (coordinate) {0});
  initialize(&Proville, "Proville", false, (coordinate) {0});
  initialize(&Provin, "Provin", false, (coordinate) {0});
  initialize(&Roucourt, "Roucourt", false, (coordinate) {0});
  initialize(&Villers_au_Tetre, "Villers-au-Tetre", false, (coordinate) {0});

  // Allied aerodromes
  initialize(&Auchel, "Auchel", true, (coordinate) {0});
  initialize(&Avesnes_le_Comte, "Avesnes-le-Comte", true, (coordinate) {0});
  initialize(&Bellevue, "Bellevue", true, (coordinate) {0});
  initialize(&Bruay, "Bruay", true, (coordinate) {0});
  initialize(&Chocques, "Chocques", true, (coordinate) {0});
  initialize(&Fienvillers, "Fienvillers", true, (coordinate) {0});
  initialize(&Fienvilliers, "Fienvilliers", true, (coordinate) {0});
  initialize(&Filescamp, "Filescamp", true, (coordinate) {0});
  initialize(&Hesdigneul, "Hesdigneul", true, (coordinate) {0});
  initialize(&LeHameau, "Le Hameau", true, (coordinate) {0});
  initialize(&Lealvillers, "Léalvillers", true, (coordinate) {0});
  initialize(&Lozingham, "Lozingham", true, (coordinate) {0});
  initialize(&Marieux, "Marieux", true, (coordinate) {0});
  initialize(&Savy, "Savy", true, (coordinate) {0});
  initialize(&Soncamp, "Soncamp", true, (coordinate) {0});
  initialize(&Treizennes, "Treizennes", true, (coordinate) {0});
  initialize(&Vert_Galand, "Vert Galand", true, (coordinate) {0});
}

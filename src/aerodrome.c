// -*- coding: iso-latin-1 -*-
#include "system.h"
#include "aerodrome.h"
#include "actor_visual.h"
#include "coordinate.h"
#include "playstate.h"
#include <stdbool.h>

#ifdef __CALYPSI_TARGET_SYSTEM_A2560U__
#include <foenix/vicky.h>
#endif

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

static void initialize(struct playstate *playstate, struct aerodrome *aerodrome,
                       char *name, bool allied, coordinate pos) {
  aerodrome->name = name;
  aerodrome->pos = pos;
  init_list(&aerodrome->flights);
  init_list(&aerodrome->airplanes);
  init_list(&aerodrome->squadron);
#if defined(__CALYPSI_TARGET_SYSTEM_A2560U__)
  set_visual_coord(&aerodrome->visual, pos);
  aerodrome->visual.actor_tile = allied ? allied_aerodrome_sprite
                                        : central_aerodrome_sprite;
#else
#error "non supported systen"
#endif
  add_tail(&playstate->aerodromes, &aerodrome->node);
  add_actor(pos, &aerodrome->visual);
}

void create_aerodromes(struct playstate *playstate) {
  // Central power aerodromes
  initialize(playstate, &Abacon, "Abacon", false, (coordinate) {0});
  initialize(playstate, &Bersee, "Bersée", false, (coordinate) {0});
  initialize(playstate, &Boistrancourt, "Boistrancourt", false, (coordinate) {0});
  initialize(playstate, &Cantin, "Cantin", false, (coordinate) {0});
  initialize(playstate, &Corbehem, "Corbehem", false, (coordinate) {0});
  initialize(playstate, &Cuincy, "Cuincy", false, (coordinate) {0});
  initialize(playstate, &Emerchicourt, "Émerchicourt", false, (coordinate) {0});
  initialize(playstate, &Epinoy, "Épinoy", false, (coordinate) {0});
  initialize(playstate, &Eswars, "Eswars", false, (coordinate) {0});
  initialize(playstate, &Faumont, "Faumont", false, (coordinate) {0});
  initialize(playstate, &Gonnelieu, "Gonnelieu", false, (coordinate) {0});
  initialize(playstate, &Guesnain, "Guesnain", false, (coordinate) {0});
  initialize(playstate, &LaBrayelle, "La Brayelle", false, (coordinate) {0});
  initialize(playstate, &Phalempin, "Phalempin", false, (coordinate) {0});
  initialize(playstate, &Pont_a_Marcq, "Pont-à-Marcq", false, (coordinate) {0});
  initialize(playstate, &Pronville, "Pronville", false, (coordinate) {0});
  initialize(playstate, &Proville, "Proville", false, (coordinate) {0});
  initialize(playstate, &Provin, "Provin", false, (coordinate) {0});
  initialize(playstate, &Roucourt, "Roucourt", false, (coordinate) {0});
  initialize(playstate, &Villers_au_Tetre, "Villers-au-Tetre", false, (coordinate) {0});

  // Allied aerodromes
  initialize(playstate, &Auchel, "Auchel", true, (coordinate) {0});
  initialize(playstate, &Avesnes_le_Comte, "Avesnes-le-Comte", true, (coordinate) {0});
  initialize(playstate, &Bellevue, "Bellevue", true, (coordinate) {0});
  initialize(playstate, &Bruay, "Bruay", true, (coordinate) {0});
  initialize(playstate, &Chocques, "Chocques", true, (coordinate) {0});
  initialize(playstate, &Fienvillers, "Fienvillers", true, (coordinate) {0});
  initialize(playstate, &Fienvilliers, "Fienvilliers", true, (coordinate) {0});
  initialize(playstate, &Filescamp, "Filescamp", true, (coordinate) {0});
  initialize(playstate, &Hesdigneul, "Hesdigneul", true, (coordinate) {0});
  initialize(playstate, &LeHameau, "Le Hameau", true, (coordinate) {0});
  initialize(playstate, &Lealvillers, "Léalvillers", true, (coordinate) {0});
  initialize(playstate, &Lozingham, "Lozingham", true, (coordinate) {14,0});
  initialize(playstate, &Marieux, "Marieux", true, (coordinate) {0});
  initialize(playstate, &Savy, "Savy", true, (coordinate) {0});
  initialize(playstate, &Soncamp, "Soncamp", true, (coordinate) {0});
  initialize(playstate, &Treizennes, "Treizennes", true, (coordinate) {0});
  initialize(playstate, &Vert_Galand, "Vert Galand", true, (coordinate) {0});
}

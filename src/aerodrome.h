#ifndef __AERODROME_H__
#define __AERODROME_H__

#include "coordinate.h"
#include "list.h"
#include "actor_visual.h"

// An aerodrome is a place where airplanes are stored, takes off from
// and can land at. They have a fixed location and identity in the map
// when they are active.
// Airplanes on the ground are either kept in a flights (group of airplanes)
// plus a flat list of airplanes that may be added to a flight.
struct aerodrome {
  struct node node;     // Belongs to a list of existing aerodromes in playstate
  struct actor_visual visual;
  const char *name;           // Name of the aerodrome
  coordinate pos;             // The sector of this aerodrome
  bool allied;                // Set if this aerodrom belongs to the allied side.
  struct list flights;        // All the flights parked here.
  struct list airplanes;      // Airplanes on the ground not currently part of a flight
  struct list squadron;       // The squadrons stationed at this aerodrome
};

extern struct aerodrome Abacon;
extern struct aerodrome Bersee;
extern struct aerodrome Boistrancourt;
extern struct aerodrome Cantin;
extern struct aerodrome Corbehem;
extern struct aerodrome Cuincy;
extern struct aerodrome Emerchicourt;
extern struct aerodrome Epinoy;
extern struct aerodrome Eswars;
extern struct aerodrome Faumont;
extern struct aerodrome Gonnelieu;
extern struct aerodrome Guesnain;
extern struct aerodrome LaBrayelle;
extern struct aerodrome Phalempin;
extern struct aerodrome Pont_a_Marcq;
extern struct aerodrome Pronville;
extern struct aerodrome Proville;
extern struct aerodrome Provin;
extern struct aerodrome Roucourt;
extern struct aerodrome Villers_au_Tetre;

extern struct aerodrome Auchel;
extern struct aerodrome Avesnes_le_Comte;
extern struct aerodrome Bellevue;
extern struct aerodrome Bruay;
extern struct aerodrome Chocques;
extern struct aerodrome Fienvillers;
extern struct aerodrome Fienvilliers;
extern struct aerodrome Filescamp;
extern struct aerodrome Hesdigneul;
extern struct aerodrome LeHameau;
extern struct aerodrome Lealvillers;
extern struct aerodrome Lozingham;
extern struct aerodrome Marieux;
extern struct aerodrome Savy;
extern struct aerodrome Soncamp;
extern struct aerodrome Treizennes;
extern struct aerodrome Vert_Galand;

// **********************************************************************

extern void create_aerodromes(struct playstate *playstate);

#endif // __AERODROME_H__

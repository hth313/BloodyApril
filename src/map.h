#ifndef __MAP_H__
#define __MAP_H__

#include "coordinate.h"
#include <stdint.h>

enum terrain {
  Lake, Forest, Field, Mountain, Swamp, River
};

// Sector types contains attributes to describe properties
// of the sector.
// The Enemy flag is set when the sector is some specific sector
// type where the presence of enemy makes sense. Water may typically
// not have this bit set.

enum terrain_attribute {
  Bridge = 1,
  Railway = 2,
  Road = 4,
  City = 8,
  Village = 16,
  Airfield = 32,
  Trench = 64,
  Enemy = 0x8000
};

struct sector {
  enum terrain_attribute terrain_attributes;
  struct {
    uint8_t spotting_range : 4;  // distance to closest spotter on group 0-15 (0-5 actully used)
    uint8_t terrain : 3;         // classification of nature terrain
    uint8_t enemy_terrain : 1;   // sector is enemy held
  };
  struct list *actors;           // actors in this sector (not including flights)
};

struct viewport {
  unsigned x;                    // offset x position
  unsigned y;                    // offset y position
  unsigned width;                // visible pixel width
  unsigned height;               // visible pixel height
};

struct map_state {
  struct viewport viewport;      // visible map in pixels
  coordinate visible_top_left;   // upper top left sector shown, potentially partial
  coordinate visible_bottom_right;
};

// **********************************************************************

#define Q_SIZE 56
#define R_SIZE 32

// Static sector data.
extern struct sector sector_data[Q_SIZE][R_SIZE];
extern unsigned q_actor_count[Q_SIZE];

#define SECTOR_ACTOR_CACHE_SIZE 8

extern struct list *hex_actor_list_cache[SECTOR_ACTOR_CACHE_SIZE];
extern unsigned hex_actor_list_cache_count;
extern bool overflowed_hex_actor_left;


// **********************************************************************

extern void clear_sectors(void);
extern void vacate_sector(coordinate coord);
extern struct list *alloc_actor_list(void);

inline void add_sector_attribute(uint_fast8_t q, uint_fast8_t r,
                                 enum terrain_attribute attr) {
  sector_data[q][r].terrain_attributes |= attr;
}

// Distribute sector terrain attribute from a list/array of coordinates
inline void add_sector_attributes(coordinate *cs, enum terrain_attribute attr) {
  while (cs->qr != CoordinateEndMarker) {
    add_sector_attribute(cs->q, cs->r, attr);
    cs++;
  }
}

inline void set_sector_attribute(uint_fast8_t q, uint_fast8_t r, enum terrain terrain) {
  sector_data[q][r].terrain = terrain;
}

inline void set_sector_terrains(coordinate *cs, enum terrain terrain) {
  while (cs->qr != CoordinateEndMarker) {
    set_sector_attribute(cs->q, cs->r, terrain);
    cs++;
  }
}

#endif // __MAP_H__

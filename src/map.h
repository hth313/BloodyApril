#ifndef __MAP_H__
#define __MAP_H__

#include "coordinate.h"

typedef enum terrain {
  Lake, Forest, Field, Mountain, Swamp, River
} terrain;

typedef enum terrain_attribute {
  Bridge = 1,
  Railway = 2,
  Road = 4,
  City = 8,
  Village = 16,
  Airfield = 32,
} terrain_attribute;

typedef struct sector {
  terrain terrain;
  terrain_attribute attrs;
} Sector;

// Placement of units are done by placing them in a hashmap keyed on two sectors.
// Normally one would put a unit in a sector, but here we allow a unit to be
// either inside a sector or occupy the border between two sectors.
// Thus, a unit can be in two sectors at a given point, or one.
// hashmap ..


#endif // __MAP_H__

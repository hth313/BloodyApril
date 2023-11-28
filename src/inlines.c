#include "airplane.h"
#include "list.h"
#include "map.h"

// airplane.h
extern bool damaged(airplane *p);

// map.h
extern void add_sector_attribute(uint_fast8_t q, uint_fast8_t r,
                                 enum terrain_attribute attr);
extern void add_sector_attributes(coordinate *cs, enum terrain_attribute attr);
extern void set_sector_attribute(uint_fast8_t q, uint_fast8_t r, enum terrain terrain);
extern void set_sector_terrains(coordinate *cs, enum terrain terrain);

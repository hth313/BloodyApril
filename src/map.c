#include "map.h"
#include <stdint.h>
#include <stdlib.h>

struct sector sector_data[Q_SIZE][R_SIZE];

void clear_sectors(void) {
  memset(sector_data, 0, sizeof(sector_data));
}

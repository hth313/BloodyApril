#include "map.h"
#include "coordinate.h"
#include "list.h"
#include "memory.h"
#include <stdint.h>
#include <stdlib.h>

struct sector sector_data[Q_SIZE][R_SIZE];
unsigned q_actor_count[Q_SIZE];
struct list *hex_actor_list_cache[SECTOR_ACTOR_CACHE_SIZE];
unsigned hex_actor_list_cache_count;
bool overflowed_hex_actor_left;

void clear_sectors(void) {
  memset(sector_data, 0, sizeof(sector_data));
}

// Call this whenever an actor is unlinked from a hex.
void vacate_sector(coordinate coord) {
  if (empty_list(sector_data[coord.q][coord.r].actors)) {
    for (unsigned i = 0; i < SECTOR_ACTOR_CACHE_SIZE; i++) {
      if (hex_actor_list_cache[i] == 0) {
        hex_actor_list_cache[i] = sector_data[coord.q][coord.r].actors;
        sector_data[coord.q][coord.r].actors = 0;
	hex_actor_list_cache_count++;
        return;
      }
    }
    // No spot in the cache, simply mark that we overflowed.
    overflowed_hex_actor_left = true;
  }
}

// Actor lists should be allocated using this function which is able to
// re-use old lists from the cache.
struct list *alloc_actor_list() {
  restart:
  if (hex_actor_list_cache_count) {
    for (unsigned i = 0;; i++) {
      struct list *p = hex_actor_list_cache[i];
      if (p != 0) {
        hex_actor_list_cache_count--;
	hex_actor_list_cache[i] = 0;
        return p;
      }
    }
  } else if (overflowed_hex_actor_left) {
    unsigned i = 0;
    for (unsigned q = 0; q < Q_SIZE; q++) {
      for (unsigned r = 0; r < R_SIZE; r++) {
	struct list *p = sector_data[q][r].actors;
        if (empty_list(p)) {
          if (i >= SECTOR_ACTOR_CACHE_SIZE) {
            goto restart;
	  }
          hex_actor_list_cache[i] = p;
          i++;
        }
      }
    }
    overflowed_hex_actor_left = false;
    goto restart;
  } else {
    return safe_malloc(sizeof(struct list));
  }
}

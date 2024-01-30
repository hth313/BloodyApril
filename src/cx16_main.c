#include "random.h"

static unsigned values[20];

int main() {
  init_seed();

  for (unsigned i = 0; i < 20; i++) {
    values[i] = roll2d10();
  }
  return 0;
}

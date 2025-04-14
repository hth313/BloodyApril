#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "random.h"
#include "system.h"
#include "scenario.h"

static unsigned values[20];
static unsigned control1, control2;

int main() {
  init_seed();

  initialize_scenarios();

  while (1) {
    static int xx;
    static char last_char;
    xx = values[5];
    if (fread(&last_char, 1, 1, stdin) == 1) {
      // got a char.
      int dice = roll2d10();
    }
  }
}

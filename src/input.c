#include <stdbool.h>
#include <stdio.h>
#include "dogfight.h"
#include "ui.h"

static bool yes_no() {
  fputs(" (press 'n' for 'no'", stdout);
  return getchar() != 'n';
}

void user_dogfight_orders(struct dogfight *df) {
  bool *p;
  cursor_to(CommandPosition);
  if (df->allied_attacker) {
    printf("Your opponent has initiative and wants to %s, do you want to keep going?",
            df->attacker_disengage ? "disengage" : "keep going");
    p = &df->defender_disengage;
  } else {
    fputs("You have initiative, do you want to continue the dogfight?", stdout);
    p = &df->attacker_disengage;
  }
  *p = !yes_no();
}

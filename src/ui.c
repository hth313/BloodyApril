#include <stdio.h>
#include "airplane.h"
#include "ui.h"
#include "squadron.h"

void show_airunit(airplane *p, bool allied) {
  const struct airplane_kind *k = p->kind;
  const struct pilot *pilot = &p->pilot;
  struct squadron *squadron = p->squadron;
  printf("%s %s %s %s", k->name, pilot->name, allied ? "from" : "aus",
         squadron->name);
}

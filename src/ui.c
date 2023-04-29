#include <stdio.h>
#include "airplane.h"
#include "ui.h"
#include "unit.h"

void show_airunit(airplane *p, bool allied) {
  struct airplane_kind *k = airplane_data[p->airplane];
  struct pilot *pilot = pilot_data[p->pilot];
  struct unit *unit = unit_data[k->unit];
  printf("%s %s %s %s", k->name, pilot->name, allied ? "from" : "aus",
         unit->name);
}

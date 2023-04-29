// -*- coding: iso-latin-1 -*-
#include "pilot.h"
#include "unit.h"

struct pilot walter_boening = {
  "Walter Böning", Jasta19, 2, 0, 1
};

struct pilot erich_hahn = {
  "Erich Hahn", Jasta19, 2, 0, 1
};

struct pilot franz_brandt = {
  "Franz Brandt", Jasta19, 2, 0, 1
};

struct pilot walther_gottisch = {
  "Walther Göttisch", Jasta19, 2, 0, 1
};

struct pilot hans_pippart = {
  "Hans Pippart", Jasta19, 2, 0, 1
};

struct pilot arthur_rahn = {
  "Arthur Rahn", Jasta19, 2, 0, 1
};

struct pilot *pilot_data[] = {
    &walter_boening, &erich_hahn, &franz_brandt, &walther_gottisch,
    &hans_pippart, &arthur_rahn,
};

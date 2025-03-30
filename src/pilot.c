// -*- coding: iso-latin-1 -*-
#include "pilot.h"
#include "squadron.h"

// Jasta 1
struct pilot paul_bona = {      // 6 kills December 1916 - May 1917
  "Paul Bona", Jasta1, 1, 0, 1
};

struct pilot wilhelm_cymera = {      // 5 victories
  "Wilhelm Cymera", Jasta1, 1, 0, 1
};

struct pilot hans_kummertz = {      // 6 victories
  "Hans Kummertz", Jasta1, 1, 0, 1
};

struct pilot herbert_schroder = {      // 5 victories
  "Herbert Shröder", Jasta1, 1, 0, 1
};

// Jasta 2

struct pilot erich_hahn = {
  "Erich Hahn", Jasta2, 2, 0, 1
};

struct pilot werner_voss = {      // 22 kills reached in early April
  "Werner Voss", Jasta2, 2, 0, 1
};

// Jasta 3

struct pilot georg_schlenker = {      // 22 kills reached in early April
  "Georg Schlenke", Jasta3, 2, 0, 1
};

struct pilot julius_schmidt = {      // 22 kills reached in early April
  "Julius Schmidt", Jasta3, 2, 0, 1
};

struct pilot carl_menckhoff = {      // 18 victories
  "Carl Menckhoff", Jasta3, 2, 0, 1
};

// Jasta 4
struct pilot fritz_otto_bernert = {      // 15 kills during Bloody April
  "Fritz Otto Bernert", Jasta4, 2, 0, 1  // in Jasta 2??
};

struct pilot wilhelm_frankl = {      // 20 kills by Bloody April
  "Wilhelm Frankl", Jasta4, 2, 0, 1  //
};

struct pilot hans_klein = {      // 3rd kill by April 4
  "Hans Klein", Jasta4, 2, 0, 1
};

struct pilot kurt_von_doring = {      // 5 kills, ended war with 11 kills
  "Kurt von Döring", Jasta4, 2, 0, 1
};

struct pilot kurt_wusthoff = {      // 5 kills, ended war with 11 kills
  "Kurt Wüsthoff", Jasta4, 2, 0, 1
};

// Jasta 5



struct pilot walter_boening = {
  "Walter Böning", Jasta19, 2, 0, 1
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

const struct pilot *pilot_data[] = {
    &walter_boening, &erich_hahn, &franz_brandt, &walther_gottisch,
    &hans_pippart, &arthur_rahn,
};

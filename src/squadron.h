#ifndef __UNIT_H__
#define __UNIT_H__

#include "list.h"

struct squadron {
  struct node node; // squadrons are linked to an aerodrome
  const char *name;
};

extern struct squadron squadron3;

extern struct squadron Jasta1;
extern struct squadron Jasta2;
struct squadron Jasta19;

#endif // __UNIT_H__

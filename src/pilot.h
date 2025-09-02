#ifndef __PILOT_H__
#define __PILOT_H__

#include "squadron.h"

struct pilot {
  char const *name;
  unsigned strength;
  unsigned duration;
  unsigned kills;
};

#endif // __PILOT_H__

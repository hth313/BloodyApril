#ifndef __PLAYFIELD_H__
#define __PLAYFIELD_H__

#include "coordinate.h"

// Sector types are returned negative to indicate enemy sector, so
// -Airfield means and enemy airfield. Water and Forest are always
// positive. For landing probabilty only the kind matters, so the
// strip_ownership() function can be applied to it.
enum sector_type {
  Plain,
  Town,
  Airfield,
  Trench,
  Water,
  Forest,
  Road,
  Railroad
};


// **********************************************************************

inline enum sector_type strip_ownership(enum sector_type s) {
  if (s < 0) {
    return (enum sector_type) -s;
  } else {
    return s;
  }
}

extern enum sector_type sector_type(coordinate location);


#endif // __PLAYFIELD_H__

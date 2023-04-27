#ifndef __PILOT_H__
#define __PILOT_H__

struct pilot {
  char const *name;
  int unit;
  unsigned strength;
  unsigned duration;
  unsigned kills;
};

// We have an array of airplane data we can look up in.
extern struct pilot pilot_data[];

#endif // __PILOT_H__

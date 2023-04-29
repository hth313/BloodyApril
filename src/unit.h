#ifndef __UNIT_H__
#define __UNIT_H__

enum unit_id { Jasta19 };

struct unit {
  char const *name;
};

// We have an array of airplane data we can look up in.
extern struct unit *unit_data[];

#endif // __UNIT_H__

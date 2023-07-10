#ifndef __UNIT_H__
#define __UNIT_H__

struct squadron {
  struct node node; // squadrons are linked to an aerodrome
  enum squadron_ident ident;
  const char *name;
};

#endif // __UNIT_H__

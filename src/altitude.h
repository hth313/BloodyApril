#ifndef __ALTITUDE_H__
#define __ALTITUDE_H__

typedef enum altitude {
  Deck, Low, Medium, High, VeryHigh
} altitude;

#define ALTITUDES (VeryHigh + 1)

#endif // __ALTITUDE_H__

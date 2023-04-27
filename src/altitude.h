#ifndef __ALTITUDE_H__
#define __ALTITUDE_H__

enum altitude_band {
  Deck, Low, Medium, High, VeryHigh
};

// There are four levels within an altitude band.
typedef unsigned int altitude_t;

#define ALTITUDE_BANDS (VeryHigh + 1)

extern enum altitude_band altitude_band(altitude_t);

#endif // __ALTITUDE_H__

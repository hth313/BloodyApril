#include "altitude.h"

enum altitude_band altitude_band(altitude_t altitude) {
  if (altitude < 4) {
    return Deck;
  } else if (altitude < 8) {
    return Low;
  } else if (altitude < 12) {
    return Medium;
  } else if (altitude < 16) {
    return High;
  } else {
    return VeryHigh;
  }
}

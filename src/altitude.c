#include "altitude.h"

enum altitude_band altitude_band(altitude_t altitude) {
  if (altitude < 4) {
    return Deck;               // 0 - 3999
  } else if (altitude < 8) {
    return Low;                // 4000 - 9999
  } else if (altitude < 12) {
    return Medium;             // 10000 - 15999
  } else if (altitude < 16) {
    return High;               // 16000 - 18999
  } else {
    return VeryHigh;           // 19000+
  }
}

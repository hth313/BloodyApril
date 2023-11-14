#include "actor_visual.h"
#include "altitude.h"
#include "coordinate.h"
#include "flight.h"
#include "list.h"
#include "weather.h"
#include <stdbool.h>

// Determine visible from ground
static bool detect_visible_ground(struct flight *flight, altitude_t *alt) {
  altitude_t lowest = MAX_ALTITUDE;
  struct airplane *airplane;
  foreach_node(*flight->airplanes, airplane) {
    if (airplane->altitude < lowest)
      lowest = airplane->altitude;
  }
  *alt = lowest;
  if (lowest <= global_weather.cloud_base) {
    return true;
  }
  unsigned intensity;
  if (lowest >= global_weather.cloud_top) {
    intensity = global_weather.cloud_intensity;
  } else {
    unsigned thickness = global_weather.cloud_top - global_weather.cloud_base;
    return (rand() % thickness) > (lowest - global_weather.cloud_base);
  }
}

bool detect_from_ground(struct playstate *playstate, struct flight *flight) {
  altitude_t lowest;
  if (detect_visible_ground(flight, &lowest)) {
    int spotting_range =
      umin(sector_data[flight->loc.main.q][flight->loc.main.r].spotting,
           sector_data[flight->loc.secondary.q][flight->loc.secondary.r].spotting);

    // Overall distance
    if (spotting_range > 5)
      return false;

    // Take daylight in account
    int hour = playstate->current_time.tm_hour;
    if ((hour == 7 || hour == 19) && spotting_range > 2) {
      // In dusk distance is limited to 2 hexes
      return false;
    } else if (hour < 8 || hour > 19) {
      return false;
    }

    unsigned base = 12;

    // Adjust for weather conditions, we are observing from ground here, so
    // everything applies.
    switch (global_weather.kind) {
    case Snow:
      base -= 5;
      break;
    case Rain:
      base -= 3;
      break;
    case Fog:
      base -= 7;
      break;
    default:
      break;
    }

    // Adjust for size of flight formation.
    unsigned flight_size = list_length(&flight->airplanes);
    if (flight_size <= 1) {
      base--;
    } else if (flight_size <= 3) {
      base += 2;
    } else {
      base += 4;
    }

    // Adjust for altitude band.
    base -= altitude_band(lowest);

    return roll2d10() >= base;
  }

  return false;
}

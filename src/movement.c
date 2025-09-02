#include <stdint.h>
#include "airplane.h"
#include "flight.h"

uint8_t allowed_turn(struct flight *flight, struct airplane *airplane) {
  if (scale_distance_to_hex(airplane->kind->speed[airplane->altitude]) >= 5) {
    return 2;
  } else {
    return 3;
  }
}

// Move a flight to a new location. This sets the location and sets its
// ability to turn in this new location.
void enter_location(struct flight *flight, location loc) {
  flight->loc = loc;

  // Restore turn ability, the "worst" airplane in the flight decides the limit.
  uint8_t free_turn = 12;
  uint8_t max_turn = 12;
  struct airplane *airplane;
  foreach_node(&flight->airplanes, airplane) {
    uint8_t turn = allowed_turn(flight, airplane);
    if (turn < free_turn)
      free_turn = turn;
    turn *= 2;           // max turn is double free turn
    if (turn < max_turn)
      max_turn = turn;
  }
  flight->free_turn = free_turn;
  flight->max_turn = max_turn;
}

// A flight turns a given angle (amount of 30 degrees).
// If flight is between hex edges, it falls into the neighboring hex in the
// direction it turns to.
// Angle given is desired turn, it may be adjusted down if it exceeds the
// ability to turn.
// The number of MP left are given updated in return. For free turns they
// will be the same, if exceeding the free turn, max turn is used and this
// will reduce the MP left.
distance_t turn_flight(struct flight *flight, distance_t mp, int8_t angle) {
  // Normalize
  uint8_t cost = angle > 0 ? angle : -angle;
  if (cost > flight->max_turn) {
    cost = flight->max_turn;
  }
  if (cost != 0) {
    if (cost > flight->free_turn) {
      mp--;
      flight->free_turn = 0;
    }
    flight->max_turn -= cost;

    // TODO: Check for falling into a hex nearby and update

    if (angle < 0) {
      if (cost > flight->heading) {
        flight->heading = 12 - (cost - flight->heading);
      } else {
        flight->heading -= cost;
      }
    } else {
      flight->heading += cost;
      if (flight->heading >= 12)
        flight->heading -= 12;
    }
  }
  return mp;
}

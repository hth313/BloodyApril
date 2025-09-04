#include "aerodrome.h"
#include "airplane.h"
#include "flight.h"
#include "practice_flying.h"
#include "playstate.h"
#include "weather.h"

void practice_flying_setup(struct playstate *playstate) {
  create_aerodromes(playstate);
  create_weather(playstate);

  static struct airplane *airplanes[] = { &Airplane_Pup, 0 };
  struct flight *flight =
    new_allied_flight(coordinate_to_location(Lozingham.pos), South, airplanes);
  add_tail(&playstate->flights, &flight->node.node);
}

void practice_flying_summarize(struct playstate *playstate) {
  // TODO: detect landing, safely or not
}

bool practice_flying_playturn(struct playstate *playstate) {
  playstate->game_ended = false;
  render(playstate);

  while (!playstate->game_ended) {
    weather_phase(playstate);
    wind_drift(playstate);
    render(playstate);
    while (true);   // wait for command here
    playstate->turn++;
  }
  return true;
}

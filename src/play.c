#include <stdbool.h>
#include <stime.h>
#include "scenario.h"

// This could be smaller, and month transition are not properly handled at the
// moment. However, converting it to time_t will will drag in a lot of library
// code that want to avoid.
static void step_time(struct playstate *state) {
  state->current_time.tm_min += 2;
  if (state->current_time.tm_min >= 60) {
    state->current_time.tm_min = 0;
    state->current_time.tm_hour += 1;
    if (state->current_time.tm_hour >= 24) {
      state->current_time.tm_hour = 0;
      state->current_time.tm_mday++;
      state->current_time.tm_wday++;
      if (state->current_time.tm_wday > 6) {
        state->current_time.tm_wday = 0;
      }
    }
  }
}

// This is the top level play loop, very simple as the scenario
// defines what happens in a turn for flexibility.
static void play(struct playstate *state) {
  while (true) {
    state.turn++;
    if (!state->scenario->playturn(state)) {
      // Game is over, allow the user to see the outcome.
      state->scenario->summarize(state);
      break;
    }
    step_time(state);
  }
}

void main(void) {
  // Initialize game system.
  struct scenarios *scenarios = initialize_scenarios();
  struct playstate state;

  while (true) {
    intro();
    state.scenario = select_a_game(scenarios);
    if (state.scenario) {
      scenario->setup(&state);
      play(&state);
    }
  }
}

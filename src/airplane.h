#ifndef __AIRPLANE_H__
#define __AIRPLANE_H__

#include <stdbool.h>
#include <stdint.h>
#include "altitude.h"
#include "coordinate.h"
#include "pilot.h"
#include "list.h"

enum token {
  TokenAlbatros_D2, TokenAlbatros_D5a, TokenSopwithPup
};

enum unit { Jasta19 };

struct airplane_kind {
  char const* name;
  altitude_t service_ceiling;
  unsigned speed[ALTITUDE_BANDS];
  unsigned climb_ability[ALTITUDE_BANDS]; // ft/round
  enum token token;                 // play token used
  enum unit unit;                   // which unit it belongs to
  unsigned firepower;
  unsigned endurance;
  unsigned agility;                 // maneuverability
  unsigned aggression;
  uint16_t property;
#define AIRPLANE_FRONT_GUN    0x0001
#define AIRPLANE_FRONT_GUNx2  0x0002
#define AIRPLANE_REAR_GUN     0x0004
};

// We have an array of airplane data we can look up in.
extern struct airplane_kind *airplane_data[];

// Airplane desribes an actual airplane player
typedef struct airplane {
  struct node   node;
  int           airplane;
  int           pilot;
  altitude_t    altitude;
  unsigned      rounds_left;
  unsigned      duration;       // number of turns in service
  unsigned      kills;          // number of kills awarded in this mission
  unsigned      stamina;
  uint16_t property;
#define AIRPLANE_FRONT_GUN_JAMMED     0x0001
#define AIRPLANE_FRONT_GUNx2_JAMMED   0x0002
#define AIRPLANE_REAR_GUN_JAMMED      0x0004
#define AIRPLANE_ENGINE_FAILURE       0x0008
#define AIRPLANE_CRIPPLED             0x0010
#define AIRPLANE_DOWNED               0x0020
#define AIRPLANE_DISENGAGE            0x0040
#define AIRPLANE_SPIN                 0x0080
  uint16_t added_property;
  location position;
  direction heading;
  uint16_t move_order;
#define AIRPLANE_ORDER_CLIMB          0x0001
#define AIRPLANE_ORDER_DECEND         0x0002
#define AIRPLANE_ORDER_SPIN_OUT       0x0004
#define AIRPLANE_TURN_LEFT            0x0008
#define AIRPLANE_TURN_RIGHT           0x0010
} airplane;

#define GUN_MASK (AIRPLANE_FRONT_GUN_JAMMED | AIRPLANE_FRONT_GUNx2_JAMMED | AIRPLANE_REAR_GUN_JAMMED)
#define OUT_MASK (AIRPLANE_ENGINE_FAILURE | AIRPLANE_CRIPPLED | AIRPLANE_DOWNED | AIRPLANE_SPIN)
#define CAN_BE_ATTACKED_MASK (AIRPLANE_ENGINE_FAILURE | AIRPLANE_DOWNED | AIRPLANE_SPIN)

// Return true if airplane is too damaged to fight
inline bool damaged(airplane* p) {
  return (p->property & (AIRPLANE_DOWNED | AIRPLANE_CRIPPLED | AIRPLANE_ENGINE_FAILURE))
          || (p->property & GUN_MASK) == (airplane_data[p->airplane].property & GUN_MASK);
}

#endif // __AIRPLANE_H__

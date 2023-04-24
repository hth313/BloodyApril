#ifndef __AIRPLANE_H__
#define __AIRPLANE_H__

#include <stdint.h>
#include "altitude.h"
#include "pilot.h"

typedef struct airplane_kind {
  char const* name;
  altitude service_ceiling;
  unsigned speed[ALTITUDES];
  unsigned climb_ability[ALTITUDES];
  int token;                        // play token used
  int unit;                         // which unit it belongs to
  unsigned firepower;
  unsigned endurance;
  uint16_t property;
#define AIRPLANE_FRONT_GUN    0x0001
#define AIRPLANE_FRONT_GUNx2  0x0002
#define AIRPLANE_REAR_GUN     0x0004
} airplane_kind;

// Airplane desribes an actual airplane player
typedef struct airplane {
  int           airplane;
  int           pilot;
  altitude      altitude;
  unsigned      rounds_left;
  unsigned      duration;       // number of turns in service
  unsigned      kills;          // number of kills awarded in this mission
  unsigned      stamina;
  uint16_t property;
#define AIRPLANE_FRONT_GUN_JAMMED     0x0001
#define AIRPLANE_FRONT_GUNx2_JAMMED   0x0002
#define AIRPLANE_READ_GUN_JAMMED      0x0004
#define AIRPLANE_ENGINE_FAILURE       0x0008
#define AIRPLANE_CRIPPLED             0x0010
#define AIRPLANE_DOWNED               0x0020
#define AIRPLANE_DISENGAGE            0x0040
#define AIRPLANE_SPIN                 0x0080
} airplane;

#endif // __AIRPLANE_H__

#ifndef __ACTOR_KIND_H__
#define __ACTOR_KIND_H__

// The order used here is intended to matter, higher numbers should
// be displayed above those with lower number.
enum actor_kind {
  Aerodrome,
  Artillery,
  LightArchie,
  MediumArchie,
  HeavyArchie,
  Infanrty,
  Cavalry,
  MachineGun,
  Ballon,       // Obseravtion ballon
  FlamingOnion, // Concentration of such
  DogFight,     // An active dogfight
  Flight,
};

#endif // __ACTOR_KIND_H__

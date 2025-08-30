#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <stdint.h>
#ifdef __CALYPSI_TARGET_SYSTEM_A2560U__
#include <foenix/gavin.h>
#endif

inline uint16_t random_u16() {
#ifdef __CALYPSI_TARGET_SYSTEM_A2560U__
  return SystemControl.random;
#else
  return rand();
#endif
}

extern void init_seed(void);
extern uint16_t roll2d10(void);
extern uint16_t rolld10(void);

#endif // __RANDOM_H__

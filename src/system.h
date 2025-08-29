#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#if defined(__CALYPSI_TARGET_SYSTEM_C256U__)
#define VRAM __attribute__((far))
#endif

#if defined(__CALYPSI_TARGET_SYSTEM_A2560U__)
#define VRAM __attribute__((far))
#endif

#ifndef VRAM
#define VRAM
#endif

#endif // __SYSTEM_H__

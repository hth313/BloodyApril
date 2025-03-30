#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#if defined(__CALYPSI_TARGET_SYSTEM_FOENIX__) && defined(__CALYPSI_TARGET_65816__)
#define VRAM __attribute__((far))
#endif

#ifdef __CALYPSI_TARGET_SYSTEM_CX16__
#define ACTOR_TILE_SIZE 1024
#define VRAM __attribute__((vram))
#define ACTOR_TILE_HEIGHT 32
#define ACTOR_TILE_COUNT 128
#endif

#if defined(__CALYPSI_TARGET_SYSTEM_AMIGA__)
#define ACTOR_TILE_HEIGHT 32
#endif

#ifndef VRAM
#define VRAM
#endif

#endif // __SYSTEM_H__

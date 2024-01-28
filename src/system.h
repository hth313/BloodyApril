#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#ifdef __CALYPSI_TARGET_SYSTEM_CX16__
#define SPRITE_SIZE 1024
#define VRAM __attribute__((vram))
#define SPRITE_HEIGHT 32
#define SPRITE_COUNT 128
#endif

#ifndef VRAM
#define VRAM
#endif

#endif // __SYSTEM_H__

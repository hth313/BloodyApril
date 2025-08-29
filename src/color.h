#ifndef __COLOR_H__
#define __COLOR_H__

#ifdef __CALYPSI_TARGET_SYSTEM_FOENIX__
#include <foenix/vicky.h>

#ifdef __CALYPSI_TARGET_65816__
#define BACKGROUND_COLOR ((color24_t){0xc6, 0xe6, 0xec})
#define BORDER_COLOR (color24_t) { 0, 0, 0 }
#endif // __CALYPSI_TARGET_65816__

#ifdef __CALYPSI_TARGET_68000__
#define BACKGROUND_COLOR 0xc6e6ec
#define BORDER_COLOR 0
#endif // __CALYPSI_TARGET_68000__

#endif // __CALYPSI_TARGET_SYSTEM_FOENIX__

#endif // __COLOR_H__

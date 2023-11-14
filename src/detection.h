#ifndef __DETECATION_H__
#define __DETECATION_H__

struct playstate;
struct flight;


// **********************************************************************

extern bool detect_from_ground(struct playstate *playstate,
                               struct flight *flight);

#endif __DETECATION_H__

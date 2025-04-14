#include <ace/managers/bob.h>
#include <stdbool.h>

extern UBYTE right_facing_dogfight_actor_data[];
extern UBYTE right_facing_dogfight_actor_mask[];

extern UBYTE left_facing_dogfight_actor_data[];
extern UBYTE left_facing_dogfight_actor_mask[];


tBob right_facing_dogfight_actor_tile;
tBob left_facing_dogfight_actor_tile;

static void create_actor(tBob *bob, UBYTE *data, UBYTE *mask) {
  bobInit(bob, 32, 32, true, data, mask, 0, 0);
}

void create_actors() {
  create_actor(&right_facing_dogfight_actor_tile,
	       right_facing_dogfight_actor_data,
	       right_facing_dogfight_actor_mask);
  create_actor(&left_facing_dogfight_actor_tile,
	       left_facing_dogfight_actor_data,
	       left_facing_dogfight_actor_mask);

}
 
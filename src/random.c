#include <stdlib.h>
#include "random.h"

#ifdef __CALYPSI_TARGET_SYSTEM_A2560U__
#include <foenix/gavin.h>
#endif

#ifdef __CALYPSI_TARGET_SYSTEM_A2560U__
void init_seed(void) { SystemControl.lfsr_enable = 1; }
#else
void init_seed(void) { srand(4711); }
#endif

// 2d10 probability table.
// reference: https://www.dragonsfoot.org/forums/viewtopic.php?t=14054
//
// 2 > 1%     1       0
// 3 > 2%     3     655
// 4 > 3%     6    1966
// 5 > 4%    10    3932
// 6 > 5%    15    6535
// 7 > 6%    21    9830
// 8 > 7%    28   13762
// 9 > 8%    36   18349
// 10 > 9%   45   23593
// 11 > 10%  55   29491
// 12 > 9%   64   36044
// 13 > 8%   72   41942
// 14 > 7%   79   47185
// 15 > 6%   85   51773
// 16 > 5%   90   55705
// 17 > 4%   94   58982
// 18 > 3%   97   61603
// 19 > 2%   99   63569
// 20 > 1%   100  64880
uint16_t roll2d10(void) {
#ifdef __CALYPSI_TARGET_SYSTEM_A2560U__
  uint16_t raw = SystemControl.random;
#else
  uint16_t raw = rand();
#endif
  if (raw > 29491) {
    // 11 - 20
    if (raw > 47185) {
      // 14 - 20
      if (raw > 55705) {
        // 16 - 20
        if (raw > 61603) {
          // 18 - 20
          if (raw > 63569) {
            /// 19 - 20
            if (raw > 64880)
              return 20;
            else
              return 19;
          } else {
            return 18;
          }
        } else {
	  // 16 - 17
          if (raw > 58982)
            return 17;
          else
            return 16;
        }
      } else {
        // 14 - 15
        if (raw > 51773)
          return 15;
        else
          return 14;
      }
    } else {
      // 11 - 13
      if (raw > 36044) {
	if (raw > 41942)
	  return 13;
	else
          return 12;
      } else {
	return 11;
      }
    }
  } else {
    // 2 - 10
    if (raw > 13762) {
      // 8 - 10
      if (raw > 23593)
        return 10;
      if (raw > 18349)
        return 9;
      else
        return 8;
    } else {
      // 2 - 7
      if (raw > 6535) {
        // 6 - 7
        if (raw > 9830)
          return 7;
        else
          return 6;
      } else {
        if (raw > 3932)
          return 5;
        if (raw > 1966)
          return 4;
        if (raw > 655)
          return 3;
        else
          return 2;
      }
    }
  }
}

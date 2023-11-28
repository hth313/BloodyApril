#include "memory.h"
#include <stdlib.h>

void *safe_malloc(size_t sz) {
  void *p = malloc(sz);
  if (!p) {
    abort();
  }
  return p;
}

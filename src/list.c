#include "list.h"
#include <mcp/syscalls.h>

void remove_node_with_interrupts_blocked(struct node *node) {
  sys_int_disable_all();
  remove_node(node);
  sys_int_enable_all();
}

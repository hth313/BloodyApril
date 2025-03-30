#include "list.h"
#ifdef __CALYPSI_TARGET_SYSTEM_FOENIX__
#include <mcp/syscalls.h>
#endif
#ifdef __CALYPSI_TARGET_65816__
#include <calypsi/intrinsics65816.h>
#endif


extern void init_list(struct list *list);
extern bool empty_list(struct list *list);
extern unsigned list_length(struct list *list);
extern void add_head(struct list *list, struct node *node);
extern void add_tail(struct list *list, struct node *node);
extern void remove_node(struct node *node);
extern void insert_after(struct node *before, struct node *new_node);
extern void predicate_insert(struct list *list, struct node *node, pred_t pred);
extern void order_insert(struct list *list, struct typed_node *node);
extern void move_members(struct list *to, struct list *from);

void remove_node_with_interrupts_blocked(struct node *node) {
#ifdef __CALYPSI_TARGET_SYSTEM_FOENIX__
  sys_int_disable_all();
#endif
#ifdef __CALYPSI_TARGET_65816__
  __interrupt_state_t istate = __get_interrupt_state();
  __disable_interrupts();
#endif

  remove_node(node);

#ifdef __CALYPSI_TARGET_SYSTEM_FOENIX__
  sys_int_enable_all();
#endif
#ifdef __CALYPSI_TARGET_65816__
  __restore_interrupt_state(istate);
#endif
}

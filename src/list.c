#include "list.h"
#include <mcp/syscalls.h>

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
  sys_int_disable_all();
  remove_node(node);
  sys_int_enable_all();
}

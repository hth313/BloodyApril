#ifndef __LIST_H__
#define __LIST_H__

#include <stdbool.h>

enum actor_kind;

struct node {
  struct node *succ;
  struct node *pred;
};

// A typed node is like a node but carries an identity to allow
// different things to be linked into it.
struct ordered_node {
  struct node node;
  int order;
};

struct list {
   struct node *head;
   struct node *tail;
   struct node *tailpred;
};

#define foreach_node(list, item) for (item = (void*)((list)->head);                 \
                                      ((struct node*)(item))->succ;                 \
                                      item = (void*)(((struct node*)(item))->succ))

#define foreach_node_safe(list, current, next)            \
  for (current = (void *)((list)->head);                  \
      (next = (void *)((struct node*)(current))->succ);   \
      current = (void *)next)


inline void init_list(struct list *list) {
  list->head = (struct node*) &list->tail;
  list->tailpred = (struct node*) &list->head;
  list->tail = 0;
}

inline bool empty_list(struct list *list) {
  return list->tailpred == (struct node *)list;
}

inline void add_head(struct list *list, struct node *node) {
  struct node *next = list->head;
  list->head = node;
  node->succ = next;
  node->pred = (struct node*)list;
  next->pred = node;
}

inline void add_tail(struct list *list, struct node *node) {
  struct node *prev = list->tailpred;
  list->tailpred = node;
  prev->succ = node;
  node->succ = (struct node*) &list->tail;
  node->pred = prev;
}

inline void remove_node(struct node *node) {
  struct node *next = node->succ;
  struct node *pred = node->pred;
  pred->succ = next;
  next->pred = pred;
}

inline void insert_after(struct node *before, struct node *new_node) {
  new_node->pred = before;
  new_node->succ = before->succ;
  before->succ->pred = new_node;
  before->succ = new_node;
}

inline void order_insert(struct list *list, struct ordered_node *node) {
  struct ordered_node *next;
  foreach_node(list, next) {
    if (next->order > node->order)
      break;
  }
  node->node.pred = next->node.pred;
  node->node.succ = &next->node;
  next->node.succ = &node->node;
  next->node.pred->succ = &node->node;
}

typedef bool (*pred_t)(struct node *current_node, struct node *next_node,
		       struct node *new_node);

inline void predicate_insert(struct list *list, struct node *node, pred_t pred) {
  struct node *current;
  foreach_node(list, current) {
    if (current->succ->succ && pred(current, current->succ, (struct node*) node)) {
      insert_after(current, (struct node*) node);
      return;
    }
  }
  add_tail(list, (struct node*) node);
}

inline void move_members(struct list *to, struct list *from) {
  if (empty_list(from)) {
    init_list(to);
  } else {
    struct node *first = from->head;
    struct node *last = from->tailpred;
    to->head = first;
    to->tailpred = last;
    to->tail = 0;
    first->pred = (struct node*)to;
    last->succ = (struct node*) &to->tail;
  }
}

// **********************************************************************

extern void remove_node_with_interrupts_blocked(struct node *node);

#endif // __LIST_H__

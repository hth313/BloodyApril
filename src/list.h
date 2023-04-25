#ifndef __LIST_H__
#define __LIST_H__

struct node {
    struct node *succ;
    struct node *pred;
};

struct list {
   struct node *head;
   struct node *tail;
   struct node *tailpred;
};

inline void init_list(struct list *list) {
  list->head = (struct node*) &list->tail;
  list->tailpred = (struct node*) &list->head;
  list->tail = 0;
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

#endif // __LIST_H__

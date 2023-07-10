#ifndef __LIST_H__
#define __LIST_H__

struct node {
    struct node *succ;
    struct node *pred;
};

enum node_kind {
  Flight.     // A flight is a group of airplanes moving together
  Dogfight,   // A dogfight keeps track of participants and corresponding action
  Ballon,     // Observation ballon
  GroundUnit  // Some ground uint, may be capable of fire on airplanes
};

// A typed node is like a node but carries an identity to allow
// different things to be linked into it.
struct typed_node {
  struct node *ty_succ;
  struct node *ty_pred;
  enum node_kind kind;
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

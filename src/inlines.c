// list.h
extern void add_head(struct list *list, struct node *node);
extern void add_tail(struct list *list, struct node *node);
extern void remove_node(struct node *node);
extern void order_insert(struct list *list, struct typed_node *node);

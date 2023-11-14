#include "airplane.h"
#include "list.h"

// list.h
extern unsigned list_length(string list *list);
extern void add_head(struct list *list, struct node *node);
extern void add_tail(struct list *list, struct node *node);
extern void remove_node(struct node *node);
extern void order_insert(struct list *list, struct typed_node *node);

// map.h
extern void add_sector_attribute(uint_fast8_t q, uint_fast8_t r,
                                 enum terrain_attribute attr);
extern void add_sector_attributes(coordinate *cs, enum terrain_attribute attr);
exterrn void set_sector_terrain(uint_fast8_t q, uint_fast8_t r, enum terrain terrain);

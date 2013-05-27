#ifndef __LIST_H__
#define __LIST_H__

#include <stdbool.h>
#include <stdint.h>
#include "stack.h"
#include "util.h"

#define LIST_VALUE stack
#define LIST_NULL_VALUE NULL
#define LIST_VALUE_PRINT_STR "%p"
#define LIST_VALUE_PRINT_SPACER " "

/* safeguard every operation? */
#define __LIST_SAFE__

typedef LIST_VALUE list_value_t;

typedef struct list_item {
	list_value_t value;
	struct list_item *next;
} list_item_t;

typedef struct list {
	list_item_t *first;
	uint size;
} list_t;

typedef list_item_t* list_item;
typedef list_t* list;

list list_create();
void list_destroy(list);
list_item list_item_create(list_value_t);
list_value_t list_item_destroy(list_item);

bool is_list_empty(list);
bool list_contains(list, list_value_t);
void list_push(list, list_value_t);
list_value_t list_pop(list list);

void list_print(list);

#endif

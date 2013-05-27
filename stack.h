#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>
#include <stdint.h>
#include "util.h"

#define STACK_VALUE uint
#define STACK_NULL_VALUE -1
#define STACK_VALUE_PRINT_STR "%lu"
#define STACK_VALUE_PRINT_SPACER " "

/* safeguard every operation? */
#define __STACK_SAFE__

typedef STACK_VALUE stack_value_t;

typedef struct stack_item {
	stack_value_t value;
	struct stack_item *next;
} stack_item_t;

typedef struct stack {
	stack_item_t *top;
	uint size;
} stack_t;

typedef stack_item_t* stack_item;
typedef stack_t* stack;

stack stack_create();
void stack_destroy(stack);
stack_item stack_item_create(stack_value_t);
stack_value_t stack_item_destroy(stack_item);

bool is_stack_empty(stack);
bool stack_contains(stack, stack_value_t);
void stack_push(stack, stack_value_t);
stack_value_t stack_pop(stack stack);

void stack_print(stack);

#endif

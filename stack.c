#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"

stack stack_create() {
	stack stack = malloc(sizeof(stack_t));
	#ifdef __STACK_SAFE__
	if(stack == NULL) {
		fputs("[STACK] [stack_create] ERROR: malloc failed\n", stderr);
		return NULL;
	}
	#endif
	stack->top = NULL;
	stack->size = 0;
	return stack;
}

void stack_destroy(stack stack) {
	stack_item i,j;
	#ifdef __STACK_SAFE__
	if (stack == NULL) {
		fputs("[STACK] [stack_destroy] ERROR: stack is a NULL pointer\n", stderr);
		return;
	}
	#endif
	i = stack->top;
	while(i != NULL) {
		j = i->next;
		stack_item_destroy(i);
		i = j;
	}
	free(stack);
}

stack_item stack_item_create(stack_value_t value) {
	stack_item item = malloc(sizeof(stack_item_t));
	#ifdef __STACK_SAFE__
	if(item == NULL) {
		fputs("[STACK] [stack_item_create] ERROR: malloc failed\n", stderr);
		return NULL;
	}
	#endif
	item->value = value;
	item->next = NULL;
	return item;
}

stack_value_t stack_item_destroy(stack_item item) {
	stack_value_t value;
	#ifdef __STACK_SAFE__
	if(item == NULL) {
		fputs("[STACK] [stack_item_destroy] ERROR: item is a NULL pointer\n", stderr);
		return STACK_NULL_VALUE;
	}
	#endif
	value = item->value;
	free(item);
	return value;
}

void stack_push(stack stack, stack_value_t value) {
	stack_item item;
	#ifdef __STACK_SAFE__
	if(stack == NULL) {
		fputs("[STACK] [stack_push] ERROR: stack is a NULL pointer\n", stderr);
		return;
	}
	#endif
	item = stack_item_create(value);
	item->next = stack->top;
	stack->top = item;
	stack->size++;
}

stack_value_t stack_pop(stack stack) {
	stack_item item;
	#ifdef __STACK_SAFE__
	if(is_stack_empty(stack)) {
		fputs("[STACK] [stack_pop] ERROR: cannot pop an empty stack\n", stderr);
		return STACK_NULL_VALUE;
	}
	#endif
	item = stack->top;
	stack->top = item->next;
	stack->size--;
	return stack_item_destroy(item);
}

bool is_stack_empty(stack stack) {
	#ifdef __STACK_SAFE__
	if(stack == NULL) {
		fputs("[STACK] [is_stack_empty] ERROR: stack is a NULL pointer\n", stderr);
		return true;
	}
	#endif
	return stack->size == 0;
}


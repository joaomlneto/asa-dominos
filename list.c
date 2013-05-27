#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

list list_create() {
	list list = malloc(sizeof(list_t));
	#ifdef __LIST_SAFE__
	if(list == NULL) {
		fputs("[LIST] [list_create] ERROR: malloc failed\n", stderr);
		return NULL;
	}
	#endif
	list->first = NULL;
	list->size = 0;
	return list;
}

void list_destroy(list list) {
	list_item i,j;
	#ifdef __LIST_SAFE__
	if (list == NULL) {
		fputs("[LIST] [list_destroy] ERROR: list is a NULL pointer\n", stderr);
		return;
	}
	#endif
	i = list->first;
	while(i != NULL) {
		j = i->next;
		stack_destroy(i->value);
		free(i);
		/*list_item_destroy(i);*/
		i = j;
	}
	free(list);
}

list_item list_item_create(list_value_t value) {
	list_item item = malloc(sizeof(list_item_t));
	#ifdef __LIST_SAFE__
	if(item == NULL) {
		fputs("[LIST] [list_item_create] ERROR: malloc failed\n", stderr);
		return NULL;
	}
	#endif
	item->value = value;
	item->next = NULL;
	return item;
}

list_value_t list_item_destroy(list_item item) {
	list_value_t value;
	#ifdef __LIST_SAFE__
	if(item == NULL) {
		fputs("[LIST] [list_item_destroy] ERROR: item is a NULL pointer\n", stderr);
		return LIST_NULL_VALUE;
	}
	#endif
	value = item->value;
	free(item);
	return value;
}

void list_push(list list, list_value_t value) {
	list_item item;
	#ifdef __LIST_SAFE__
	if(list == NULL) {
		fputs("[LIST] [list_push] ERROR: list is a NULL pointer\n", stderr);
		return;
	}
	#endif
	item = list_item_create(value);
	item->next = list->first;
	list->first = item;
	list->size++;
}

list_value_t list_pop(list list) {
	list_item item;
	#ifdef __LIST_SAFE__
	if(is_list_empty(list)) {
		fputs("[LIST] [list_pop] ERROR: cannot pop an empty list\n", stderr);
		return LIST_NULL_VALUE;
	}
	#endif
	item = list->first;
	list->first = item->next;
	list->size--;
	return list_item_destroy(item);
}

bool is_list_empty(list list) {
	#ifdef __LIST_SAFE__
	if(list == NULL) {
		fputs("[LIST] [is_list_empty] ERROR: list is a NULL pointer\n", stderr);
		return true;
	}
	#endif
	return list->size == 0;
}

bool list_contains(list list, list_value_t value) {
	list_item i;
	#ifdef __LIST_SAFE__
	if(list == NULL) {
		fputs("[LIST] [list_contains] ERROR: list is a NULL pointer\n", stderr);
		return false;
	}
	#endif
	for (i = list->first; i != NULL; i = i->next) {
		if(i->value == value) {
			return true;
		}
	}
	return false;
}


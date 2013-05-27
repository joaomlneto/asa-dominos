#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <stdint.h>
#include <stdbool.h>

#define sint long int
#define uint unsigned long int

#define MIN(X,Y) ((X)<(Y)?(X):(Y))
#define MAX(X,Y) ((X)>(Y)?(X):(Y))

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

typedef struct testcase {
	uint num_dominos;
	uint optimal_solution;
	stack *drops;
} testcase_t;
typedef testcase_t* testcase;

uint read_int();
void read_int_pair(uint *a, uint *b);
uint get_num_tests();

testcase testcase_create(uint num_dominos);
testcase read_test_case();

void print_testcase(testcase);
void print_digraph(testcase);

#define TARJAN_UNDEFINED_INDEX -1

typedef struct tarjan {
	testcase testcase;
	uint index;
	stack stack;
	uint *vertex_index;
	uint *vertex_lowlink;
	list sccs;
} tarjan_t;
typedef tarjan_t* tarjan;

uint count_unreachable_sccs(testcase);
list tarjan_scc(testcase);
void tarjan_strongconnect(tarjan, uint index);

#define BUFFER_SIZE 16

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

bool stack_contains(stack stack, stack_value_t value) {
	stack_item i;
	#ifdef __STACK_SAFE__
	if(stack == NULL) {
		fputs("[STACK] [stack_contains] ERROR: stack is a NULL pointer\n", stderr);
		return false;
	}
	#endif
	for (i = stack->top; i != NULL; i = i->next) {
		if(i->value == value) {
			return true;
		}
	}
	return false;
}

void stack_print(stack stack) {
	stack_item i;
	printf("[Top] ");
	for (i = stack->top; i != NULL; i = i->next) {
		printf(STACK_VALUE_PRINT_STR, i->value);
		printf(STACK_VALUE_PRINT_SPACER);
	}
	printf("[Bottom]\n");
}

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
		list_item_destroy(i);
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

void list_print(list list) {
	list_item i;
	printf(">>> LIST START\n");
	for (i = list->first; i != NULL; i = i->next) {
		stack_print((stack)i->value);
	}
	printf("<<< LIST END\n");
}

uint read_int() {
	uint value;
	scanf("%lu\n", &value);
	return value;
}

void read_int_pair(uint *a, uint *b) {
	scanf("%lu %lu\n", a, b);
}

uint get_num_tests() {
	return read_int();
}

testcase testcase_create(uint num_dominos) {
	uint i;
	testcase testcase = malloc(sizeof(testcase_t));
	testcase->num_dominos = num_dominos;
	testcase->optimal_solution = 0;
	testcase->drops = malloc(num_dominos*sizeof(stack));
	for(i=0; i<num_dominos; i++) {
		testcase->drops[i] = stack_create();
	}
	return testcase;
}

testcase read_test_case() {
	testcase testcase;
	uint num_dominos, num_drops, i;
	read_int_pair(&num_dominos, &num_drops);
	testcase = testcase_create(num_dominos);
	for(i=0; i<num_drops; i++) {
		uint a, b;
		read_int_pair(&a, &b);
		/* shift domino number to match vector index */
		stack_push(testcase->drops[a-1], b-1);
	}
	return testcase;
}

void print_digraph(testcase testcase) {
	uint i;
	stack stack;
	stack_item j;
	static uint count = 1;
	printf("digraph testcase%lu {\n", count++);
	for( i=0; i<testcase->num_dominos; i++) {
		printf("\t%lu;\n", i+1);
		stack = testcase->drops[i];
		for(j = stack->top; j != NULL; j = j->next) {
			printf("\t%lu -> %lu;\n", i+1, j->value);
		}
	}
}

void print_testcase(testcase testcase) {
	uint i;
	printf("\n[TESTCASE]\n");
	printf("num dominos: %lu\noptimal solution:%lu\n",
	       testcase->num_dominos, testcase->optimal_solution);
	for(i=0; i<testcase->num_dominos; i++) {
		printf("Domino %lu: ", i+1);
		stack_print(testcase->drops[i]);
	}
	printf("--------------\n");
}

tarjan tarjan_create(testcase testcase) {
	tarjan tarjan = malloc(sizeof(tarjan_t));
	size_t i;
	tarjan->testcase = testcase;
	tarjan->index = 0;
	tarjan->stack = stack_create();
	tarjan->vertex_index = malloc(testcase->num_dominos*sizeof(sint));
	tarjan->vertex_lowlink = malloc(testcase->num_dominos*sizeof(uint));
	tarjan->sccs = list_create();
	for(i=0; i<testcase->num_dominos; i++) {
		tarjan->vertex_index[i] = TARJAN_UNDEFINED_INDEX;
	}
	return tarjan;
}

list tarjan_destroy(tarjan t) {
	list sccs = t->sccs;
	stack_destroy(t->stack);
	free(t->vertex_index);
	free(t->vertex_lowlink);
	free(t);
	return sccs;
}

uint count_unreachable_sccs(testcase tc) {

	list_item i;
	stack_item j, k;
	uint count, l;

	/* get set of SCCs */
	list sccs = tarjan_scc(tc);

	/* map domino number to corresponding scc number */
	uint *scc_number = malloc(tc->num_dominos*sizeof(uint));
	uint *stamp = malloc(sccs->size*sizeof(uint));
	count = 0;
	for(i = sccs->first; i != NULL; i = i->next, count++) {
		stack s = i->value;
		for(j = s->top; j != NULL; j = j->next) {
			scc_number[j->value] = count;
		}
	}

	/* checks which sccs have edges to them from other sccs */
	for(l=0; l<sccs->size; l++) {
		stamp[l] = 1;
	}

	/* for each SCC */
	for(i = sccs->first; i != NULL; i = i->next) {
		/* for each vertex in the SCC */
		for(j = i->value->top; j != NULL; j = j->next) {
			uint v = j->value;
			/* for each edge from v */
			for(k = tc->drops[v]->top; k != NULL; k = k->next) {
				uint w = k->value;
				/* there's an edge from vertex V to W */
				if(scc_number[v] != scc_number[w]) {
					stamp[scc_number[w]] = 0;
				}
			}
		}
	}

	count = 0;
	for(l=0; l<sccs->size; l++) {
		count += stamp[l];
	}
	
	return count;
}

list tarjan_scc(testcase testcase) {
	uint i;
	tarjan tarjan = tarjan_create(testcase);
	for(i=0; i<testcase->num_dominos; i++) {
		if(tarjan->vertex_index[i] == TARJAN_UNDEFINED_INDEX) {
			tarjan_strongconnect(tarjan, i);
		}
	}
	return tarjan_destroy(tarjan);
}

void tarjan_strongconnect(tarjan t, uint v) {
	stack_item i;
	t->vertex_index[v] = t->index;
	t->vertex_lowlink[v] = t->index;
	t->index++;
	stack_push(t->stack, v);
	/* Consider successors of v */
	for(i = t->testcase->drops[v]->top; i != NULL; i = i->next) {
		uint w = i->value;
		if(t->vertex_index[w] == TARJAN_UNDEFINED_INDEX) {
			/* Successor w has not yet been visited; recurse on it */
			tarjan_strongconnect(t, w);
			t->vertex_lowlink[v] = MIN(t->vertex_lowlink[v], t->vertex_lowlink[w]);
		}
		else if(stack_contains(t->stack, w)) {
			/* Successor w is in stack S and hence in the current SCC */
			t->vertex_lowlink[v] = MIN(t->vertex_lowlink[v], t->vertex_index[w]);
		}
	}
	/* If v is a root node, pop the stack and generate a SCC */
	if (t->vertex_lowlink[v] == t->vertex_index[v]) {
		stack scc = stack_create();
		uint w;
		do {
			w = stack_pop(t->stack);
			stack_push(scc, w);
		} while (w != v);
		list_push(t->sccs, scc);
	}
}

int main() {
	uint num_tests = get_num_tests();
	testcase testcase;
	uint i;
	for(i=0; i<num_tests; i++) {
		testcase = read_test_case();
		printf("%lu\n", count_unreachable_sccs(testcase));
	}
	return 0;
}

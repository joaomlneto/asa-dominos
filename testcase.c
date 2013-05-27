#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "testcase.h"

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
	testcase->drops = malloc(num_dominos*sizeof(stack));
	for(i=0; i<num_dominos; i++) {
		testcase->drops[i] = stack_create();
	}
	return testcase;
}

void testcase_destroy(testcase t) {
	uint i;
	for(i=0; i<t->num_dominos; i++) {
		stack_destroy(t->drops[i]);
	}
	free(t->drops);
	free(t);
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
		printf("\t%lu;\n", i);
		stack = testcase->drops[i];
		for(j = stack->top; j != NULL; j = j->next) {
			printf("\t%lu -> %lu;\n", i, j->value);
		}
	}
	printf("}\n");
}


#ifndef __TARJAN_H__
#define __TARJAN_H__

#include "list.h"
#include "stack.h"
#include "testcase.h"

#define TARJAN_UNDEFINED_INDEX -1

typedef struct tarjan {
	testcase testcase;
	uint index;
	stack stack;
	bool *stack_contents;
	sint *vertex_index;
	uint *vertex_lowlink;
	list sccs;
} tarjan_t;
typedef tarjan_t* tarjan;

tarjan tarjan_create(testcase);
list tarjan_destroy(tarjan);

uint count_unreachable_sccs(testcase);
list tarjan_scc(testcase);
void tarjan_strongconnect(tarjan, uint index);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "stack.h"
#include "tarjan.h"
#include "testcase.h"
#include "util.h"

tarjan tarjan_create(testcase testcase) {
	tarjan tarjan = malloc(sizeof(tarjan_t));
	size_t i;
	tarjan->testcase = testcase;
	tarjan->index = 0;
	tarjan->stack = stack_create();
	tarjan->stack_contents = malloc(testcase->num_dominos*sizeof(uint));
	tarjan->vertex_index = malloc(testcase->num_dominos*sizeof(sint));
	tarjan->vertex_lowlink = malloc(testcase->num_dominos*sizeof(uint));
	tarjan->sccs = list_create();
	for(i=0; i<testcase->num_dominos; i++) {
		tarjan->vertex_index[i] = TARJAN_UNDEFINED_INDEX;
		tarjan->stack_contents[i] = false;
	}
	return tarjan;
}

list tarjan_destroy(tarjan t) {
	list sccs = t->sccs;
	stack_destroy(t->stack);
	free(t->stack_contents);
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

	list_destroy(sccs);
	free(scc_number);
	free(stamp);
	
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
	/* make the search for vertexes constant */
	t->stack_contents[v] = true;

	/* Consider successors of v */
	for(i = t->testcase->drops[v]->top; i != NULL; i = i->next) {
		uint w = i->value;
		if(t->vertex_index[w] == TARJAN_UNDEFINED_INDEX) {
			/* Successor w has not yet been visited; recurse on it */
			tarjan_strongconnect(t, w);
			t->vertex_lowlink[v] = MIN(t->vertex_lowlink[v], t->vertex_lowlink[w]);
		}
		/*else if(stack_contains(t->stack, w)) {*/
		else if (t->stack_contents[w]) {
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
			t->stack_contents[w] = false;
			stack_push(scc, w);
		} while (w != v);
		list_push(t->sccs, scc);
	}
}

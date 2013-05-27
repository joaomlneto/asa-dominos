#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "tarjan.h"
#include "testcase.h"

#define BUFFER_SIZE 16

int main() {
	uint num_tests = get_num_tests();
	testcase testcase;
	uint i;
	for(i=0; i<num_tests; i++) {
		testcase = read_test_case();
		/*print_digraph(testcase);*/
		printf("%lu\n", count_unreachable_sccs(testcase));
		testcase_destroy(testcase);
	}
	return 0;
}

#ifndef __TESTCASE_H__
#define __TESTCASE_H__

#include "stack.h"
#include "util.h"

typedef struct testcase {
	uint num_dominos;
	stack *drops;
} testcase_t;
typedef testcase_t* testcase;

uint read_int();
void read_int_pair(uint *a, uint *b);
uint get_num_tests();

testcase testcase_create(uint num_dominos);
void testcase_destroy(testcase);
testcase read_test_case();

void print_testcase(testcase);
void print_digraph(testcase);

#endif

#include <stdio.h>

#define NUM_REPEATS 10
#define MAX_DOMINOS 1

int main(int argc, char* argv[]) {
	int i, j;
	int num_dominos = strtol(argv[1], NULL, 10);
	printf("%d\n", NUM_REPEATS); // 1 test case
	for(i=0; i<NUM_REPEATS; i++) {
		printf("%d %d\n", num_dominos, num_dominos-1+1);
		for(j=1; j<num_dominos; j++) {
			printf("%d %d\n", j, j+1);
		}
		printf("%d %d\n", num_dominos, 1);
	}
	return 0;
}

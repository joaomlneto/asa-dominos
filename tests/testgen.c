#include <stdio.h>

#define MAX_DOMINOS 1000000

int main() {
	int i;
	printf("1\n"); // 1 test case
	printf("%d %d\n", MAX_DOMINOS, MAX_DOMINOS-1);
	for(i=1; i<MAX_DOMINOS; i++) {
		printf("1 %d\n", i+1);
	}
	return 0;
}

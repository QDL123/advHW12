#include <stdio.h>
#include <string.h>
#include<stdlib.h>

#define LONG_TIME (0xffffffff/8)

void child1(void) {
	printf("\n     Inside child1()\n");
	int i = 0;

	for( ; i < (LONG_TIME * 2); i++) {
		// Prevent the compiler from optimizing out empty loop
		asm("nop;");
	}

	return;
}

void child2(void) {
	int i = 0;

	for( ; i < 16; i++) {
		// Prevent the compiler from optimizing out empty loop
		asm("nop;");
	}

	return;
}

void parent(void) {
	printf("\n   Inside parent \n");
	int i = 0;

	for (i=0 ; i < (LONG_TIME); i++) {
		// Prevent the compiler from optimizing out empty loop
		asm("nop;");
	}
	child1();

	printf("\n     Starting child2() loop\n");
	for (i=0 ; i < (LONG_TIME/2); i++) {
		child2();
	}

	return;
}

static void no_children(void) {
	printf("\n   Inside no_children \n");
	int i = 0;

	for (i=0; i < (LONG_TIME * 5); i++) {
		// Prevent the compiler from optimizing out empty loop
		asm("nop;");
	}

	return;
}

void branchFunction(int prob) {
	for(int i = 0; i < 100; ++i) {
		int num = 100*rand();
		if(num < prob) {
			asm("nop;");
		}
	}
}

int main(int argc, char **argv) {

	int prob1 = atoi(argv[1]);
	int prob2 = atoi(argv[2]);
	int prob3 = atoi(argv[3]);

	branchFunction(prob1);
	branchFunction(prob2);
	branchFunction(prob3);

	printf("\n Inside main()\n");
	int i = 0;

	parent();
	no_children();

	printf("\n Exiting \n");
	return 0;
}

#include <stdio.h>

#include "mymath.h"

int main() {
	printf("Running a c-demonstration program that will use a header file.\n");
	// We're using the add function from mymath library.
	printf("I use add function on 4 + 8 = %d\n", add(4, 8));
	return 0;	
}

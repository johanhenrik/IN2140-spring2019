#include <stdio.h>


// Exercise a.
int ishex(unsigned char c) {
	printf("char is read as : %d.\n", c);
	// Testing with '1'.
	if (c > 47 && c < 58
			|| c > 96 && c < 103
			|| c > 64 && c < 71) {
		return 1;
	}
	return 0;		
}

// Exercise b.
/*
 * Returns -1 if the character argument is invalid.
 */
int hexval(unsigned char c) {
	if (!ishex(c)) {
		return -1;
	}
	if (c > 47 && c < 58) {
		return c - 48;
	} else if (c > 96 && c < 103) {
		return c - 87;
	} else {
		return c - 55;
	}

}


int main() {
	ishex('0');
	ishex('2');
	ishex('4');
	ishex('5');
	ishex('9');
	ishex('1');
	ishex('a');
	ishex('f');
	ishex('g');
	ishex('A');
	ishex('F');
	ishex('G');
	printf("Printing the characters: 0, 5, 9, a, e, A, F");
	printf("0 = %d\n", hexval('0'));
	printf("5 = %d\n", hexval('5'));
	printf("9 = %d\n", hexval('9'));
	printf("a = %d\n", hexval('a'));
	printf("e = %d\n", hexval('e'));
	printf("A = %d\n", hexval('A'));
	printf("F = %d\n", hexval('F'));
}

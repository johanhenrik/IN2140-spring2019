#include <stdio.h>

/*
 *     2 ( 1 bit/s)
 *     4 ( 2 bit/s)
 *     8 ( 3 bit/s)
 *    16 ( 4 bit/s)
 *    32 ( 5 bit/s)
 *    64 ( 6 bit/s)
 *   128 ( 7 bit/s)
 *   256 ( 8 bit/s)
 *   512 ( 9 bit/s)
 *  1024 (10 bit/s)
 *  2048 (11 bit/s)
 *  4096 (12 bit/s)
 *  8192 (13 bit/s)
 * 16384 (14 bit/s)
 * 32768 (15 bit/s)
 *
 * A short uses two bytes of storage (16 byte). The max and min numbers are
 * 32767 and -32768. The reasion why the max number isn't 32768 is that the
 * number 0 is also included. The max value of a short uses 15 bits, that is
 * because the lats bit is used for decising whether a number is positive or
 * negative.
 *
 * What happens in a c-program if the number 32767 is incremented is that the
 * value is changed to -32768, which is the smallest value that a short can
 * have.
 */
int main() {
	short a, b, sum;
	a = 20000; b = 20000; sum = a+b;
	printf("%d + %d = %d\n", a, b, sum);
	sum = 0;
	/*
	 * The following loop prints each short value from 0 until max value for
	 * short, then the minimum value is printed and the loop ends. This loop
	 * shows how the c-compiler will perform:
	 * 32767 + 1 = - 32768.
	 */
	// do {
	// printf("Number is : %d\n", ++sum);	
	// } while(sum > 0);
}

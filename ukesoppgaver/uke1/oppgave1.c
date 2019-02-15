#include <stdio.h>

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("Program requires an additional input argument for running.\n");
		return 1;
	}
	char *msg = argv[1];
	printf("Input: %s\n", msg);


	int NUMBER = 0;
	int NOT_A_NUMBER = 1;

	int state = NUMBER;

	// Trying to loop over the array.
	int index = 0;
	int strlen = 0;
	while (msg[index] != '\0') {
		if (msg[index] > '9' || msg[index] < '0') {
			state = NOT_A_NUMBER;
		}
		index++; strlen++;
	}
	if (state == NUMBER) {
		int tracker = strlen;
		int number = 0;
		int multiply_with_ten_count = 0;
		while (tracker > 0) {
			int digit = msg[--tracker] - 48;
			for (int i=0; i<multiply_with_ten_count; i++) {
				digit *= 10;				
			}
			multiply_with_ten_count++;
			printf("%10d\n", digit);
			number += digit;
		}
		printf("Has number : %d\n.", number);
	}
	return 0;
}


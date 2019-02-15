#include <stdio.h>

int STREQ(char s1[], char s2[]) {
	int index = 0;
	for (;;) {
		if (s1[index] == '\0' && s2[index] == '\0') {
			return 1;
		} else if (s1[index] != s2[index]) {
			return 0;
		}
		index++;
		// if (index > 20) {
		// 	printf("Error - index > 20.\n");
		// 	return 0;
		// }
	}	
}

int main() {
	char s1[] = "Hello";
	char s2[] = "Hello";
	char s3[] = "Hello World";
	if (STREQ(s1, s2)) {
		printf("This function worked on (%s, %s)!\n", s1, s2);
	}
	if (!STREQ(s1, s3)) {
		printf("Correct result also on (%s, %s)!\n", s1, s3);
	}
}

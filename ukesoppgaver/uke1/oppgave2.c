#include <stdio.h>

/*
 * SYNOPSIS
 *      char strgetc(char s[], int pos);
 *
 * DESCRIPTION
 *      The strgetc() function reads a c-string and returns the char at the
 *      position specified by the pos argument. This function iterates over the
 *      entire string searching for the character at the specified index. Thus,
 *      this function runs in linear time and much faster approaches exists.
 *      This method might however be useful. This function will never iterate
 *      outside the range of s.
 * 
 * RETURN VALUE
 *      Upon successfully return, the character at position pos is returned, 
 *      otherwise '\0' is returned.
 */
char strgetc(char s[], int pos) {
	int index = 0;
	do {
		if (index == pos) {
			return s[index];
		}
	} while (s[++index] != '\0');
	return '\0';
}

int main() {
	char text[] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
	printf("I try to access element o in 'Hello world!' : %c\n", strgetc(text, 4));
}

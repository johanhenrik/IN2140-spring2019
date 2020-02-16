#include <stdio.h>
#include <stdlib.h>

#include "util.h"

unsigned int eval_hexadecimal(char hexadecimal[], int bytes) {
    int i, j;
    int number = 0, new_round_digit_1, new_round_digit_2;
    int multiplier_count = 0;
    for (i=0; i<bytes; i++) {
        new_round_digit_1 = hexval(hexadecimal[i*2]) * 16;
        new_round_digit_2 = hexval(hexadecimal[i*2+1]);
        for (j=0; j<multiplier_count*2; j++) {
            new_round_digit_1 *= 16;
            new_round_digit_2 *=16;
        }
        multiplier_count++;
        number += new_round_digit_1 + new_round_digit_2;
    }
    return number;
}

/*
 * Allocates memory for the next single word read. A byte for one additional
 * character is allocated for the NULL value.
 */
char* get_next(size_t *index, char string[]) {
    size_t i;
    size_t string_start = *index;
    // 32 is the space character (' ') and 10 is the newline character.
    while (string[*index] != 32 && string[*index] != 10) {
         *index += 1;
    }
    char *word = malloc((*index - string_start) * sizeof(char) + 1);
    for (i=string_start; i<*index; i++) {
        word[i - string_start] = string[i];
    }
    // Terminates string with a NULL.
    word[i - string_start] = 0;
    return word;
}

/*
 * This method starts with skipping each space character (32 = ' '). Then a
 * string with size 4 is created for storing a char. 4 characters is 
 * sufficient, because max value that an unsigned char might have is 255.
 * Then the string is parsed as an unsigned char.
 *
 */
unsigned char get_next_char(size_t *index, char string[]) {
    size_t digits= *index;
    while(string[*index] == 32) {
        *index += 1;
    }

    size_t number_start = *index;
    char numstr[4];
    char digit_count = 0;
    while (string[*index] > 48 && string[*index] < 58
            && digit_count < 4) {
         numstr[*index - number_start] = string[*index];
         *index += 1;
         digit_count++;
    }
    // Prevents program from reading the same char by next read.
    *index += 1;
    char c;
	int tracker = digit_count;
	char number = 0;
	int multiply_with_ten_count = 0;
	while (tracker > 0) {
		char digit = numstr[--tracker] - 48;
		for (int i=0; i<multiply_with_ten_count; i++) {
			digit *= 10;				
		}
		multiply_with_ten_count++;
		number += digit;
	}
    return number;
}

char* get_next_line(size_t *index, char string[]) {
    // A line ends either with the NULL character (0, '\0') or
    // with a new line symbol (10 '\n').
    size_t i;
    if (string[*index] == 10 && string[*index] == 0) {
        printf("Error - get_next_line(size_t *index, char string[])\n" \
                "Reading string started at a newline or NULL character.\n");
        return NULL;
    }
    size_t string_start = *index;
    do {
        *index += 1;
    } while(string[*index] != 10 && string[*index] != 00);
    char *line = malloc((*index - string_start) * sizeof(char) + 1);
    for (i=string_start; i<*index; i++) {
        line[i - string_start] = string[i];
    }
    // Reading index must be incremented for skipping some characters.
    *index += 1;
    // Terminates string with a NULL.
    line[i - string_start] = 0;
    return line;
}

int hexval(unsigned char c) {
    if (c > 47 && c < 58) {
        return c - 48;
    } else if (c > 96 && c < 103) {
        return c - 87;
    } else {
        return c - 55;
    }
}



int ishex(unsigned char c) {
    if (c > 47 && c < 58
            || c > 96 && c < 103
            || c > 64 && c < 71) {
        return 1;
    }
    return 0;
}

void remove_white_spaces(char *string) {
    int i;
    int new_string_index = 0;
    for (i=0; i<100; i++) {
        if (*(string+i) == '\0') {
            // Must terminate tail from new string!
            *(string+new_string_index) = '\0';
            break;
        } else if (*(string+i) == ' ') {
            continue;
        } else {
            *(string+new_string_index) = *(string+i);
            new_string_index++;
        }
    }
}

int streq(char s1[], char s2[]) {
	int index = 0;
	for (;;) {
		if (s1[index] == '\0' && s2[index] == '\0') {
			return 1;
		} else if (s1[index] != s2[index]) {
			return 0;
		}
		index++;
	}
}

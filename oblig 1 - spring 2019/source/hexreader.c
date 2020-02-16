#include <stdio.h>
#include <stdlib.h>

#include "util.h"

char* read(unsigned char hexadecimals[], size_t *read_index, int bytes) {
    unsigned short j;
    char byte[3];
    /*
     * Allocates memory for a word. The byte argument specifies how many bytes
     * are required for storing the word.
     */
    unsigned char *string = malloc((bytes) * 2 * sizeof(char));
    for (j = 0; j<bytes; j++) {
        sprintf(byte, "%02x", hexadecimals[j + *read_index]);
        string[j*2] = byte[0];
        string[j*2 + 1] = byte[1];
    }
    *read_index += j;
    return string;
}

unsigned char read_char(unsigned char hexadecimal[], size_t *read_index) {
    char *_char;
    _char = read(hexadecimal, read_index, 1);
    unsigned char c = eval_hexadecimal(_char, 1);
    free(_char);
    return c;
}

int read_int(unsigned char hexadecimals[], size_t *read_index) {
    char *_int = read(hexadecimals, read_index, 4);
    int value = eval_hexadecimal(_int, 4);
    free(_int);
    // swallows the new line character.
    read_char(hexadecimals, read_index);
    return value;
}

/*
 * Warning - never used.
 *
 * Function working, but is never used.
 */
char* read_line(unsigned char hexadecimals[], size_t *read_index) {
    size_t i, j;
    char byte[3];
    unsigned char *string;
    // Ignore white spaces.
    while (hexadecimals[*read_index] == 32) {
        *read_index += 1;
    }

    string = malloc((256) * 2 * sizeof(char));
    for (j = 0; j<256; j++) {
        i=0;
        sprintf(byte, "%02x", hexadecimals[j + *read_index]);
        string[j] = eval_hexadecimal(byte, 1);
        if (streq(byte, "0a")) {
            break;
        }
    }
    string[j] = 0;
    // Pluss one because we want to skip the new line sign.
    *read_index += j + 1;
    return string;
}
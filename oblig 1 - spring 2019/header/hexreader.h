#ifndef HEXWRITER_H
#define HEXWRITER_H

/*
 * SYNOPSIS
 *      unsigned char read_char(unsigned char *hexadecimal, size_t *read_index)
 *
 * DESCRIPTION
 *      The read_char() function takes a c-string containing only hexadecimals
 *      and reads two characters as a hexadecimal and then evaluates the value
 *      as a one byte digit (unsigned char).
 *
 *      Which characters to read is specified by the read_index pointer,
 *      where the indexes read_index and read_index + 1 are read.
 *
 *      Note: the read_char function makes it easier reading single byte
 *      digits than using the read function. The read_char funtion allocates
 *      memory for a c-string (of length two) evalutes the value of the
 *      hexadecimal, frees all memory allocated for the string and then
 *      returns the value of the char. Using the read function results with
 *      memory leak if the returned value is not freed. THe following code:
 *
 *      char *_c = read(string, &index, 1);
 *      unsigned char c = eval_hexadecimal(_c, 1);
 *      free(_char);
 *
 *      is written as a oneliner, using the read_char function:
 *
 *      unsigned char c = read_char(string, &index);
 *
 * RETURN VALUE
 *      Calculates the value of hexadecimal as an unsigned char. If any error
 *      occurs during evaluation, no specification for the return value is
 *      given.
 */
    // The read function returns a char pointer which has allocated memory on
    // the heap. This memory must be freed after iteration is finished, thus,
    // every pointer returned by the free function is destroyed after use.
char* read(unsigned char hexadecimals[], size_t *read_index, int bytes);

/*
 * SYNOPSIS
 *      unsigned char read_char(unsigned char *hexadecimal, size_t *read_index)
 *
 * DESCRIPTION
 *      The read_char() function takes a c-string containing only hexadecimals
 *      and reads two characters as a hexadecimal and then evaluates the value
 *      as a one byte digit (unsigned char).
 *
 *      Which characters to read is specified by the read_index pointer,
 *      where the indexes read_index and read_index + 1 are read.
 *
 *      Note: the read_char function makes it easier reading single byte
 *      digits than using the read function. The read_char funtion allocates
 *      memory for a c-string (of length two) evalutes the value of the
 *      hexadecimal, frees all memory allocated for the string and then
 *      returns the value of the char. Using the read function results with
 *      memory leak if the returned value is not freed. THe following code:
 *
 *      char *_c = read(string, &index, 1);
 *      unsigned char c = eval_hexadecimal(_c, 1);
 *      free(_char);
 *
 *      is written as a oneliner, using the read_char function:
 *
 *      unsigned char c = read_char(string, &index);
 *
 * RETURN VALUE
 *      Calculates the value of hexadecimal as an unsigned char. If any error
 *      occurs during evaluation, no specification for the return value is
 *      given.
 */
unsigned char read_char(unsigned char hexadecimal[], size_t *read_index);

/*
 * SYNOPSIS
 *      int read_int(unsigned char hexadecimals[], size_t *read_index)
 *
 * DESCRIPTION
 *      The read_int() function takes a c-string containing only hexadecimals
 *      and reads eight characters as a hexadecimal and then evaluates the value
 *      as a four bytes digit (signed int).
 *
 *      Which characters to read is specified by the read_index pointer,
 *      where the indexes read_index and read_index + 1 are read.
 *
 * RETURN VALUE
 *      Calculates the value of hexadecimal as a signed integer. If any error
 *      occurs during evaluation, no specification for the return value is
 *      given.
 */
int read_int(unsigned char hexadecimals[], size_t *read_index);

/*
 * Reads a line from hexadecimals starting at read_index. Reading is
 * stopped when "0a" is encountered.
 */
char* read_line(unsigned char hexadecimals[], size_t *read_index);

#endif

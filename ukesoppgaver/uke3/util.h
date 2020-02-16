#ifndef __UTIL_H__
#define __UTIL_H__

/*
 * SYNOPSIS
 *      int eval_hexadecimal(char hexadecimal[], int bytes);
 *
 * DESCRIPTION
 *      The eval_hexadecimal() function takes a c-string containing a
 *      hexadecimal and evaluates its value. The hexadecimal is evaluated
 *      in "Little Endian Order". This function can evaluate any hexadecimal
 *      on the range 00 00 00 00 - FF FF FF FF (this funcion accepts both
 *      lower case and upper case input arguments)
 *
 *      The second argument specifies how many bytes the hexvalue contains.
 *
 *      Note: this function cannot handle white spaces within the hexadecimal
 *      string and it does not check for whether the hexadecimal and the bytes
 *      arguments have valid values.
 *
 * RETURN VALUE
 *      Calculates the value of hexadecimal as an unsigned int. If any error
 *      occurs during evaluation, no specification for the return value is
 *      given.
 *
 *  SEE ALSO
 *      parser.c #parse_hexadecimal(char *hexadecimal) - If the hexadecimal-
 *      argument is given from an unknown source, such as file input or as a
 *      user input, then the parse-hexadecimal function is better suited for
 *      evaluating the hexadecimal. The parser.c file is more user-friendly
 *      allowing the user to write strings with white spaces, and it
 *      writes error messages to the console, rather than returning values that
 *      might either crash the program or result in unexpected behavior.
 *
 *      The parse_hexadecimal function also runs without a byte argument
 *      provided and it also checks whether each character might be
 *      interpreted as a hexadecimal.
 */
unsigned int eval_hexadecimal(char hexadecimal[], int bytes);

/*
 * SYNOPSIS
 *      char* get_next(size_t *index, char string[]);
 *
 * DESCRIPTION
 *      The get_next() function takes a c-string and the current read index and
 *		parses the next word from the string. If this read method encounters a
 *		newline character or a space character, then the parsing terminates.
 *
 *		Note: this method increments the reading index as it reads.
 *
 * RETURN VALUE
 *      Returns the next single word from string starting at index.
 */
char* get_next(size_t *index, char string[]);

/*
 * SYNOPSIS
 *      unsigned char get_next_char(size_t *index, char string[]);
 *
 * DESCRIPTION
 *      The get_next_char() function takes a c-string and the current
 *		read index and parses the next unsigned char from it. A string
 * 		containing spaces like "    4" is successfully evaluated as 4.
 *
 *		Note: this method increments the reading index as it reads.
 *
 * RETURN VALUE
 *      Returns the next occuring unsigned char from string starting at index.
 */
unsigned char get_next_char(size_t *index, char string[]);

/*
 * SYNOPSIS
 *      char* get_next_char(size_t *index, char string[]);
 *
 * DESCRIPTION
 *      The get_next_line() function takes a c-string and the current read
 *		index and parses the next line from it, i.e. every character until a
 *		newline is encountered (10, '\n').
 *
 *		Note: this method increments the reading index as it reads.
 *
 * RETURN VALUE
 *      Returns the next occuring line, starting at index.
 */
char* get_next_line(size_t *index, char string[]);

/*
 * SYNOPSIS
 *      int hexval(unsigned char c);
 *
 * DESCRIPTION
 *      The hexval() function takes a characteras as an argument and calculates
 *      the hexadecimal value for this character.
 *
 * RETURN VALUE
 *      returns the hexadecimal value of the passed char.
 *
 * SEE ALSO
 *      parser.c #ishex(unsigned char c) - if there is no
 *      guarantee for c being a hexadecimal, then one can use ishex first, in
 *      order for guaranteing that c can be interpretet as a hexidecimal.
 */
int hexval(unsigned char c);

/*
 * SYNOPSIS
 *      int ishex(unsigned char c);
 *
 * DESCRIPTION
 *      The hexval() function takes a characteras as an argument and checks
 *      whether it can be handled as a hexadecimal or not. Both
 *      uppercase and lowercase letters are accepted as input arguments.
 *
 * RETURN VALUE
 *      true - if the char can be interpreted as a hexadecimal, false
 *      otherwise.
 */
int ishex(unsigned char c);

/*
 * SYNOPSIS
 *      void remove_white_spaces(char *string);
 *
 * DESCRIPTION
 *      The remove_white_spaces() function takes a a pointer to a c-string
 *      and removes white spaces from it, in order words, this function
 *      removes every blank character ' ' from a c-string.
 */
void remove_white_spaces(char *string);

/*
 * SYNOPSIS
 *      int streq(char s1[], char s2[]);
 *
 * DESCRIPTION
 *      The streq() function takes two string arguments and checks whether they
 *      represent the same string.
 *
 * RETURN VALUE
 *      true - if the strings are equal, false otherwise.
 */
int streq(char s1[], char s2[]);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hexreader.h"
#include "oblig.h"
#include "router.h"
#include "test.h"
#include "util.h"

/* ------------------------------------------------------------------------- *\
 *
 * Global variables.
 *
\* ------------------------------------------------------------------------- */
int N;

struct router **routers;

/* ------------------------------------------------------------------------- *\
    Methods that interacts with routers. These methods are not placed
    in the router.c file, because they function as graph methods.

    I haven't done any effort into implementing a graph.
\* ------------------------------------------------------------------------- */

void create_connection(unsigned char from, unsigned char to) {
    size_t i = 0;
    struct router *router_from = get_router(from);
	struct router *router_to = get_router(to);
	for (i=0; i<10; i++) {
        if (router_from->connections[i] == NULL) {
            // printf("NULL Adding connection from() to ()\n" \
		    //     "%s\n%s\n", router_to_string(router_from), router_to_string(router_to));
            router_from->connections[i] = router_to;
            break;
        }
    }
}

void delete(unsigned char router_id) {
    size_t i, j;
    unsigned short router_index;
    /*
     * Successfully removes every pointer that point to the router with the
     * given router_id.
     * 
     */
    for (i=0; i<N; i++) {
        if (routers[i]->router_id == router_id) {
            router_index = i;
            continue;
        } else {
            for (j=0; j<10; j++) {
                if (routers[i]->connections[j] != NULL) {
                    struct router *r = routers[i]->connections[j];
                    if (r->router_id == router_id) {
                        // Removes pointer from router to the route that is
                        // set to be deleted.
                        routers[i]->connections[j] = NULL;
                    }
                }
            }
        }
    }
    /*
     * Moves every router that are to the right of the deleted router to the 
     * left. The deleted router must be freed, otherwise the reference to the
     * memory is lost.
     */
    free(routers[router_index]);
    for (i=router_index; i<N-1; i++) {
        routers[i] = routers[i+1];
    }
    routers[N-1] = NULL;
    N--;
}

struct router* get_router(unsigned char router_id) {
    size_t i;
    for (i=0; i<N; i++) {
        if (routers[i]->router_id == router_id) {
            return routers[i];
        }
    }
    return NULL;
}

void print_each() {
    size_t i;
    for (i=0; i<N; i++) {
        struct router *r = routers[i];
        print_router(r->router_id);
    }
}

void print_router(unsigned char router_id) {
    size_t i;
    struct router *r = get_router(router_id);
    // String representatrion of a router is maximum 512 bytes.
    char *string = router_to_string(r);
    printf("%s\n", string);
    free(string);
    for (i=0; i<10; i++) {
        if (r->connections[i] == NULL) {
            continue;
        } else {
            struct router *c = r->connections[i];
            printf("\t-> %d (%s)\n", c->router_id, c->desc);
        }
    }
}

void execute(char action[]) {
    printf("%s\n", action);
    size_t read_index = 0;
    char* first_word = get_next(&read_index, action);
    if (streq(first_word, "print")) {
        printf("\t");
        print_router(get_next_char(&read_index, action));
    } else if (streq(first_word, "legg_til_kobling")) {
        create_connection(
        		get_next_char(&read_index, action),
        		get_next_char(&read_index, action));
    } else if (streq(first_word, "sett_modell")){
        struct router* r = get_router(get_next_char(&read_index, action));
        char *new_desc = get_next_line(&read_index, action);
        router_set_desc(new_desc, r);
        // Frees memory from get_next_line.
        free(new_desc);
    } else if (streq(first_word, "slett_router")) {
        delete(get_next_char(&read_index, action));
    } else if (streq(first_word, "sett_flag")){
        struct router *r = get_router(get_next_char(&read_index, action));
        unsigned char bit_index = get_next_char(&read_index, action);
        unsigned char value = get_next_char(&read_index, action);
        set_flag(r, bit_index, value);
    }
    free(first_word);
}

void execute_commands(char file_name[]) {
    FILE *fs;
    size_t i, j, read_index;
    char file_content[10000];
    fs = fopen(file_name, "r");
    if (fs == NULL ) {
        printf("Error - execute_commands(char file_name)\n" \
                "Failed to open file with name - %s\n", 
                file_name);
        return;
    }
    size_t file_length = fread(file_content, sizeof(unsigned char), 10000, fs);
    read_index = 0;
    while (read_index < file_length) {
    	char *line = get_next_line(&read_index, file_content);
    	execute(line);
    	free(line);
    }
    fclose(fs);
}

/*
 * SYNOPSIS
 *      unsigned int parse_hexadecimal(char *hexadecimal[]);
 *
 * DESCRIPTION
 *      The parse_hexadecimal() function takes a c-string containing a
 *      hexadecimal and evaluates its value. The hexadecimal is evaluated
 *      in "Little Endian Order". This function can evaluate any hexadecimal
 *      on the range 00 00 00 00 - FF FF FF FF (this funcion accepts both
 *      lower case and upper case input arguments)
 *
 *      There is, however, one constraint on the c-string argument pointer. The
 *      string must contain either 8, 16, 32 or 64 bits. Giving a c-string that
 *      is neither 1, 2, 3 or 4 bytes long cannot be evaluated by this parser.
 *      Thus, a string argument like 'AAA' results in an error.
 *
 * RETURN VALUE
 *      Upon successfully return, a non-negative integer is returned. If an
 *      error occured while executing this function. then an error-message is
 *      written to the console and 0 is returned.
 */
unsigned int parse_hexadecimal(char *hexadecimal) {
    remove_white_spaces(hexadecimal);
    int i;
    int length = strlen(hexadecimal);
    for (i=0; i<length; i++) {
        if (!ishex(hexadecimal[i])) {
            printf("Error - string \"%s\" contains nonhexadecimal values.\n",
                hexadecimal);
            printf("\tparser.c #parse_hexadecimal(char *hexadecimal)\n");
            return 0;
        }
    }
    if (length % 2!= 0) {
        printf("Error - string \"%s\" does not consist of exactly 1, 2, 3 " \
            "or 4 bytes of data.\n", hexadecimal);
            printf("\tparser.c #parse_hexadecimal(char *hexadecimal)\n");
        return 0;
    }
    return eval_hexadecimal(hexadecimal, length/2);
}

void routers_free() {
    size_t i;
    for (i=0; i<N; i++) {
        free(routers[i]);
    }
    free(routers);
}

void routers_read(char file_name[]) {
    size_t i, read_index;
    FILE *fs;
    unsigned char file_content[10000];
    fs = fopen(file_name, "r");
    if (fs == NULL ) {
        printf("Error - routers_read(char file_name)\n" \
                "Failed to open file with name - %s\n", 
                file_name);
        return;
    }
    size_t file_length = fread(file_content, sizeof(unsigned char), 10000, fs);
    read_index = 0;
    N = read_int(file_content, &read_index);
    routers = malloc(N * sizeof(struct router*));
    for (i=0; i<N; i++) {
        routers[i] = parse_router(file_content, &read_index);
    }
    while (read_index < file_length) {
        unsigned char from = read_char(file_content, &read_index);
        unsigned char to = read_char(file_content, &read_index);
        create_connection(from, to);
        //swallaws new line.
        read_char(file_content, &read_index);
    }
    fclose(fs);
}

void routers_write(char file_name[]) {
    size_t i;
    FILE *fs;
    char new_line = '\n';
    fs = fopen(file_name, "wb");
    if (fs == NULL ) {
        printf("Error - routers_write(char file_name)\n" \
                "Failed to open file with name - %s\n", 
                file_name);
        return;
    }
    fwrite(&N, sizeof(int), 1, fs);
    fwrite(&new_line, sizeof(char), 1, fs);
    for (i=0; i<N; i++) {
        serialize(fs, routers[i]);
        fwrite(&new_line, sizeof(char), 1, fs);
    }
    for (i=0; i<N; i++) {
        serialize_connections(fs, routers[i]);
    }
    fclose(fs);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        test();
        return EXIT_SUCCESS;
    }
    if (argc != 3) {
        printf("Error - main(int argc, char *argv[])\n" \
                "Wrong count of input arguments, should be 0 or 2, but was: " \
            "%d\n", argc-1);
        return EXIT_FAILURE;
    }
    routers_read(argv[1]);
    // print_each(); // Uncomment to see initial router states.
    execute_commands(argv[2]);
    // routers_write(argv[1]);
    // print_each(); // Uncomment to see result on routers.
    routers_free();
    return EXIT_SUCCESS;
}


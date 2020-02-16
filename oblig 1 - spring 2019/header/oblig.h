#ifndef OBLIG_H
#define OBLIG_H

/* ------------------------------------------------------------------------- *\
 *
 * Global variables, which are also used from test.c
 *
\* ------------------------------------------------------------------------- */
extern int N;
 
extern struct router **routers;

/* ------------------------------------------------------------------------- *\
 *
 * Function declarations.
 *
\* ------------------------------------------------------------------------- */

void create_connection(unsigned char from, unsigned char to);

void execute_commands(char file_name[]);

struct router* get_router(unsigned char router_id);

unsigned int parse_hexadecimal(char *hexadecimal);

void print_each();

void print_router(unsigned char router_id);

void routers_free();

void routers_read(char file_name[]);

void routers_write(char file_name[]);

#endif
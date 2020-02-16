#ifndef ROUTER_H
#define ROUTER_H

struct router {
    unsigned char router_id;
    unsigned char FLAGG;
    unsigned char desc_length;
    char desc[253];
    struct router *connections[10];
};

struct router* parse_router(char *file_content, size_t *read_index);

struct router* router_create(
        unsigned char router_id,
        unsigned char FLAGG,
        unsigned char desc_length,
        char desc[]);

void router_destroy(struct router *r);

void router_set_desc(char desc[], struct router *r);

char* router_to_string(struct router* r);

/*
 * Writes a binary representation of a router to the given file stream. A
 * router is written first by id, FLAGG, desc_length and the string desc.
 * The string does not end with a NULL char.
 */
void serialize(FILE *file_stream, struct router *r);

void serialize_connections(FILE *file_stream, struct router *r);

void set_flag(struct router *r, unsigned char bit_index, unsigned char value);

#endif
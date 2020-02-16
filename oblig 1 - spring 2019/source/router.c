#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hexreader.h"
#include "router.h"
#include "util.h"

struct router* router_create(
        unsigned char router_id,
        unsigned char FLAGG,
        unsigned char desc_length,
        char desc[]) {
    size_t i;
    // Allocates memory for a router struct. A router takes 256 bytes,
    // and an additional 40 bytes for pointers on 32-bits operating systems
    // or an additional 80 bytes for pointers on 64-bits operating systems.
    struct router* new_router = malloc(sizeof(struct router));
    new_router->router_id = router_id;
    new_router->FLAGG = FLAGG;
    new_router->desc_length = desc_length;
    strncpy(new_router->desc, desc, 253);
    for (i=0; i<10; i++) {
        new_router->connections[i] = NULL;
    }
    return new_router;
}

void router_set_desc(char desc[], struct router *r) {
    strncpy(r->desc, desc, 253);
    r->desc_length = strlen(desc);
}

/*
 * 512 bytes for a string describing a router should be sufficient.
 */
char *router_to_string(struct router* r) {
    char *router_info = malloc(512);
    sprintf(router_info, "struct router [router_id=%d, FLAGG=%d, " \
        "desc_length=%d, desc=%s]", r->router_id, r->FLAGG,
        r->desc_length, r->desc);
    return router_info;
}

struct router* parse_router(char *hexadecimals, size_t *read_index) {
    int i;

    unsigned char router_id = read_char(hexadecimals, read_index);    
    unsigned char FLAGG = read_char(hexadecimals, read_index);    
    unsigned char desc_length = read_char(hexadecimals, read_index);
    char desc[desc_length];
    /* --------------------------------------------------------------------- *\
     * When reading from the binary file, the string (string_description) ends
     * up with the form "example\n". When evaluating these values as char,
     * then the '\0' character is evaluated as 10, which corresponds to the
     * newline character (ASCII).
     *
     * Each router description ends with the newline character (which is found)
     * at index = string-length - 1.
    \* --------------------------------------------------------------------- */
    // Manually places a '\0' at the end of the string.
    desc[desc_length-1] = 0;
    for (i=0; i<desc_length-1; i++) {
        desc[i] = read_char(hexadecimals, read_index);
    }
    // Swallows the newline character.
    read_char(hexadecimals, read_index);
	return router_create(router_id, FLAGG, desc_length, desc);
}

void serialize(FILE *file_stream, struct router *r) {
    fwrite(&r->router_id, sizeof(char), 1, file_stream);
    fwrite(&r->FLAGG, sizeof(char), 1, file_stream);
    fwrite(&r->desc_length, sizeof(char) , 1, file_stream);
    fwrite(&r->desc, r->desc_length * sizeof(char)-1, 1, file_stream);
}

void serialize_connections(FILE *file_stream, struct router *r) {
    size_t i;
    char new_line = '\n';
    for (i=0; i<10; i++) {
        if (r->connections[i] != NULL) {
            fwrite(&r->router_id, sizeof(char), 1, file_stream);
            fwrite(&r->connections[i]->router_id, sizeof(char), 1, file_stream);
            fwrite(&new_line, sizeof(char), 1, file_stream);
        }
    }
}

void set_flag(struct router *r, unsigned char bit_index, unsigned char value) {
	unsigned char FLAGG = r->FLAGG;
	if (bit_index == 3) {
		printf("Illegal operation.\n" \
                "\tThe bit with index - 3, cannot be changed.\n" \
                "\tReturns without changing flag value.\n");
        return;
	} else if (bit_index < 4) {
		if (value < 2) {
			if (value) {
				FLAGG |= 1UL << bit_index;
			} else {
				FLAGG &= ~(1UL << bit_index);
			}
		} else {
			printf("Illegal value.\n");
		}
	} else if (bit_index == 4) {
		if (value < 16) {
			FLAGG &= ~(1UL << 5);
			FLAGG &= ~(1UL << 6);
			FLAGG &= ~(1UL << 7);
			FLAGG &= ~(1UL << 8);
			unsigned char change_number;
			change_number = 2*2*2*2*value;
			FLAGG += change_number;
		}
	} else {
		printf("ERROR - sett_flagg()\n" \
				"\tIllegal argument - bit_index\n" \
				"\tpossible values: [0, 15]");
        return;
	}
    r->FLAGG = FLAGG;
}

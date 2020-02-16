#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hexreader.h"
#include "oblig.h"
#include "router.h"
#include "util.h"

void test() {
    int i;
    // Trying to remove spaces from a string.
    char test_string_1[] = "This is my string with white spaces";
    printf(" TEST 1 (void remove_white_spaces(char* string))\n" \
        "Trying to remove white spaces from the string:" \
        "\n\t\"%s\"\n",
        test_string_1);
    remove_white_spaces(&test_string_1[0]);
    printf("which gives:\n\t%s\n\n\n", test_string_1);

    // Testing whether the exceptions are working correctly for my
    // hexadecimal function.
    printf(" TEST 2 (unsigned int parse_hexadecimal(char *hexadecimal))\n"\
        "Parsing a string containing nonhexadecimal values\n" \
        "should fail and result with an exception being written to the\n" \
        "console.\n");
    char test_string_2_1[] = "m2";
    char test_string_2_2[] = "M2";
    printf("Trying to parse value from \"%s\"\n", test_string_2_1);
    parse_hexadecimal(test_string_2_1);
    printf("Trying to parse value from \"%s\"\n", test_string_2_2);
    parse_hexadecimal(test_string_2_2);
    printf("\n\n");

    // Checking whether the parse_hexadecimal function accepts both uppercase
    // and lowercase letters.
    char test_string_3_1[] = "02af";
    char test_string_3_2[] = "02AF";
    printf(" TEST 3 (unsigned int parse_hexadecimal(char *hexadecimal))\n" \
        "Parsing strings \"%s\" and \"%s\" should both run " \
        "wihtout any\nerrors or warning messages being written to the " \
        "console.\n\n", test_string_3_1, test_string_3_2);
    parse_hexadecimal(test_string_3_1);
    parse_hexadecimal(test_string_3_2);

    // Trying to parse an integer value from a string consisting of a
    // non-even count of characters should fail.
    char test_string_4_1[] = "2";
    char test_string_4_2[] = "000";
    char test_string_4_3[] = "a0a0a";
    printf(" TEST 4 (unsigned int parse_hexadecimal(char *hexadecimal))\n" \
        "My parser-function accept only strings containing av even amount of\n" \
        "characters. This test tries to parse the following strings:\n" \
        "\t\"%s\"\n\t\"%s\"\n\t\"%s\"\n",
        test_string_4_1, test_string_4_2, test_string_4_3);
    printf("Parsing value from \"%s\"\n", test_string_4_1);
    parse_hexadecimal(test_string_4_1);
    printf("Parsing value from \"%s\"\n", test_string_4_2);
    parse_hexadecimal(test_string_4_2);
    printf("Parsing value from \"%s\"\n", test_string_4_3);
    parse_hexadecimal(test_string_4_3);
    printf("\n");

    // Testing whether parse_hexadecimal gives correct results!
    char test_strings_5[4][12];
    int correct_values[] = {15, 31, 300, 1026594};
    strncpy(test_strings_5[0], "0F 00 00 00", 12);  //        15
    strncpy(test_strings_5[1], "1F 00 00 00", 12);  //        31
    strncpy(test_strings_5[2], "2C 01 00 00", 12);  //       300
    strncpy(test_strings_5[3], "22 AA 0F 00", 12);  // 1,026,594
    printf("TEST 5 (unsigned int parse_hexadecimal(char *hexadecimal))\n" \
        "Checking whether the parse_hexadecimal function gives correct " \
        "results\n");
    for (i=0; i<4; i++) {
        printf("String: %s gets value: %d (%d)\n", test_strings_5[i],
        parse_hexadecimal(test_strings_5[i]), correct_values[i]);
    }

    printf("\n\nTEST 6, 7, 8 and 9 focuses on reading information from the " \
        "file.\n\t\"5_routers_fully_connected\"\n\n");
    FILE *fs_test;
    fs_test = fopen("5_routers_fully_connected", "r");
    if (fs_test == NULL ) {
        return;
    }
    unsigned char file_content[10000];
    size_t file_length = fread(file_content, sizeof(unsigned char), 10000, fs_test);
    printf(" TEST 6 (parse_router_count(file_content, &read_index))" \
        "\nChecking whether router count is correctly read.\n");
    size_t read_index = 0;
    int router_count = read_int(file_content, &read_index);
	N = router_count;
    printf("router count - %d\n\n", router_count);

    printf(" TEST 7 (read_line(file_content, &read_index))" \
        "\nChecking whether the router's content is correctly read.\n");
    printf("router index\tvalue\n");
    char *router_content = read_line(file_content, &read_index);
    printf("%5d  %s\n", i, router_content);
    free(router_content);
    // for (i=0; i<router_count; i++) {
    //     char *router_content;
    //     // router_content = read_line(file_content, &read_index);
    //     // printf("%5d  %s\n", i, router_content);
    //     free(router_content);
    // }
    printf("\n");

    // Zero memory leak on TEST 7.
    printf(" TEST 8\nI cannot use the read_line method on each router, " \
        "because the\nrouters content can contain the '0a' value, which " \
        "terminates\nmy read_line function.\n" \
        "Therefore, I'd rather stick with only the read function.\n");
    read_index = 5;
    char* read_router_id = read(file_content, &read_index, 1);
    unsigned char router_id = eval_hexadecimal(read_router_id, 1);
    free(read_router_id);
    char* read_FLAGG = read(file_content, &read_index, 1);
    unsigned char FLAGG = eval_hexadecimal(read_FLAGG, 1);
    free(read_FLAGG);
    char* read_desc_length = read(file_content, &read_index, 1);
    unsigned char desc_length = eval_hexadecimal(read_desc_length, 1);
    char desc[desc_length];
    free(read_desc_length);
    /* --------------------------------------------------------------------- *\
     * When reading from the binary file, the string (string_description) ends
     * up with the form "example\n". When evaluating these values as char,
     * then the '\0' character is evaluated as 10, which corresponds to the
     * newline character (ASCII).
     *
     * Each router description ends with the newline character (which is found)
     * ad index = string-length - 1. Rather than using the newline character, I
     * use the null character 00 ('\0'). The problem with useing '\n' is that
     * C doesn't know when to stop writing a string which does not end with the
     * null character.
    \* --------------------------------------------------------------------- */
    // Manually places a '\0' at the end of the string.
    desc[desc_length-1] = 0;
    for (i=0; i<desc_length-1; i++) {
        char *loop_memory = read(file_content, &read_index, 1);
        desc[i] = eval_hexadecimal(loop_memory, 1);
        printf("index . %d (%2ld) -- %c (%d)\n",i, read_index,
        desc[i], desc[i]);
        free(loop_memory);
    }
    printf("\n\trouter_id - %d\n", router_id);
    printf("\tFLAGG - %d\n", FLAGG);
    printf("\tlength - %d\n", desc_length);
    printf("\tproducer/model - %s\n\n", desc);

    printf(" TEST 8\n unsigned char read_char()\n" \
        "The read_char function makes it easier reading a single char form \n" \
        "a c-string. The read_char function automatically frees all memory \n" \
        "allocated from the read function, and thus, avoids use of pointers \n" \
        "and free functions within the method-implementations.\n\n" \
        "The code:\n\tchar *_char = read(file, &index, 1);" \
        "\n\tunsigned char c = eval_hexadecimal(_char, 1);" \
        "\n\tfree(_char)\ncan be written as:\n" \
        "\tunsigned char c = read_char(file, &index)\n");
    read_index = 5;
    unsigned char test_8_router_id = read_char(file_content, &read_index);
    unsigned char test_8_FLAGG = read_char(file_content, &read_index);
    unsigned char test_8_desc_length = read_char(file_content, &read_index);
    char test_8_desc[desc_length];
    // Manually places a '\0' at the end of the string.
    test_8_desc[test_8_desc_length-1] = 0;
    for (i=0; i<test_8_desc_length-1; i++) {
        test_8_desc[i] = read_char(file_content, &read_index);
        printf("index . %d (%2ld) -- %c (%d)\n",i, read_index,
        test_8_desc[i], test_8_desc[i]);
    }
    printf("\n\trouter_id - %d\n", test_8_router_id);
    printf("\tFLAGG - %d\n", test_8_FLAGG);
    printf("\tlength - %d\n", test_8_desc_length);
    printf("\tproducer/model - %s\n\n", test_8_desc);

    printf(" TEST 10 (parse_router(file_content, &read_index),\n" \
        "\trouter_to_string(struct router* r))\n" \
        "This test reads each router from the simples file, and writes \n" \
        "their to_string method to the console.\n\n");
    read_index = 5;
    for (i=0; i<5; i++) {
        struct router* r = parse_router(file_content, &read_index);
        char *router_info = router_to_string(r);
        printf("%s\n", router_info);
        free(router_info);
        free(r);
    }
    printf("\n");

    printf(" TEST 11 ()\n" \
        "Adds routers to the global double pointer..\n" \
        "This method also frees the memory allocated for the routers.");

    read_index = 5;
    routers = malloc(router_count * sizeof(struct router*));
    for (i=0; i<router_count; i++) {
        routers[i] = parse_router(file_content, &read_index);
        char *router_info = router_to_string(routers[i]);
        printf("%s\n", router_info);
        free(router_info);
    }
    printf("\n");
    for (i=0; i<router_count; i++) {
        free(routers[i]);
    }
    free(routers);

    printf(" TEST 12()\n");
    printf("\tAccessing router 2 from get_router.\n");
    printf("VERY IMPORTANT NOTE:\n\n" \
        "The router received with get_router does not need to be freed.\n");
    read_index = 5;
    routers = malloc(router_count * sizeof(struct router*));
    for (i=0; i<router_count; i++) {
        routers[i] = parse_router(file_content, &read_index);
    }
    struct router *test_11_r = get_router(2);
    char *test_11_string = router_to_string(test_11_r);
    printf("%s\n\n", test_11_string);
    free(test_11_string);
    // free(test_11_r);
    for (i=0; i<router_count; i++) {
        free(routers[i]);
    }
    free(routers);

    printf(" TEST 13()\n");
    read_index = 5;
    routers = malloc(router_count * sizeof(struct router*));
    for (i=0; i<router_count; i++) {
        routers[i] = parse_router(file_content, &read_index);
        char *router_info = router_to_string(routers[i]);
        printf("%s\n", router_info);
        free(router_info);
    }
    read_index = 77;
    printf("Checking whether correct indexes are written out.\n");
    while (read_index < file_length) {
        printf("Create connection : (%2d, %2d)\n",
            read_char(file_content, &read_index),
            read_char(file_content, &read_index));
        // printf("%s\n", read(file_content, &read_index, 1));
    }
    for (i=0; i<router_count; i++) {
        free(routers[i]);
    }
    free(routers);
    printf("\n");

    printf(" TEST 14(void create_connection(unsigned char from, unsigned char to);)\n");
    read_index = 5;
    routers = malloc(router_count * sizeof(struct router*));
    for (i=0; i<router_count; i++) {
        routers[i] = parse_router(file_content, &read_index);
    }
    read_index = 77;
    printf("Creates connections.\n");
    while (read_index < file_length) {
        unsigned char from = read_char(file_content, &read_index);
        unsigned char to = read_char(file_content, &read_index);
        create_connection(from, to);
        //swallaws new line.
        read_char(file_content, &read_index);
    }
    for (i=0; i<router_count; i++) {
        free(routers[i]);
    }
    free(routers);
    printf("\n");

    printf(" TEST 15(void print_router(unsigned char router_id); )\n");
    printf("This test runs the print_router on the router with id 4.\n");
    read_index = 5;
    routers = malloc(router_count * sizeof(struct router*));
    for (i=0; i<router_count; i++) {
        routers[i] = parse_router(file_content, &read_index);
    }
    print_router(4);
    for (i=0; i<router_count; i++) {
        free(routers[i]);
    }
    free(routers);
    printf("\n");

    printf(" TEST 16(void router_set_desc(char desc[], struct router *r); )\n");
    printf("Updates the name of \"Cisco o1000\" to \"Johan Henrik\" \n");
    read_index = 5;
    routers = malloc(router_count * sizeof(struct router*));
    for (i=0; i<router_count; i++) {
        routers[i] = parse_router(file_content, &read_index);
    }
    struct router *r_test_15 = get_router(1);
    router_set_desc("Johan Henrik", r_test_15);
    char *string_test_15 = router_to_string(r_test_15);
    printf("%s\n", string_test_15);
    free(string_test_15);
    for (i=0; i<router_count; i++) {
        free(routers[i]);
    }
    free(routers);
    printf("\n");
    fclose(fs_test);



    printf(" TEST 17 ()\n" \
        "A very simple test for reading \"print 1\" as a string.\n" \
        "Note: the method now reads every line from the file as a string.\n");
    FILE *fs_commands;
    fs_commands = fopen("commands_10_routers.txt", "r");
    if (fs_commands == NULL ) {
        return;
    }
    unsigned char file_commands[10000];
    size_t file_length_commands = fread(file_commands, sizeof(unsigned char), 10000, fs_commands);
    // printf("%s\n\n", file_commands);
    printf("Length if file is %ld\n", file_length_commands);
    size_t string_index;
    size_t string_start = 0;
    size_t string_end;

    for (read_index=0; read_index<file_length_commands; read_index++) {
        if (file_commands[read_index] == 10) {
            string_end = read_index;
            char string[string_end - string_start + 1];
            for (string_index=0; string_index<string_end - string_start;
                    string_index++) {
                string[string_index] = file_commands[string_start + string_index];
            }
            string[string_index] = 0;
            printf("%s\n", string);
            string_start = read_index+1;
        }
    }
    fclose(fs_commands);
    printf("\n\n");

    printf("Test 18 (routers read and free\n" \
        "Checking whether routers_read and routers_free rints without any\n" \
        "any problems.\n");
    routers_read("5_routers_fully_connected");
    routers_free();
    printf("\n");

    printf("Test 19 (get_next_line())\n" \
            "Using get_next_line on the text:\n\n");
    char long_text[] = (
            "Im Weltraum will die Menschheit ihre Zukunft sichern. Weil\n" \
            "die Erde nicht genug ist, sollen Menschen in den nächsten\n" \
            "Jahrzehnten regelmäßig ins All reisen – darunter\n" \
            "Astronautinnen, die auf Raumstationen forschen, und Touristen,\n" \
            " die den Mond umkreisen. Selbst eine Basis in Mondnähe soll\n" \
            "gebaut werden. Und vielleicht fliegt noch in diesem Jahrhundert\n" \
            "eine erste Delegation zum Mars.");
    printf("%s\n\n", long_text);
    read_index = 0;
    char *line = get_next_line(&read_index, long_text);
    printf("First line is: %s\n", line);
    free(line);
    line = get_next_line(&read_index, long_text);
    printf("Second line is: %s\n\n", line);
    free(line);

    printf("Test 20 (get_next_line())\n" \
            "Makes sure that streq gives true on:\n" \
            "\"Im Weltraum will die Menschheit ihre Zukunft sichern. Weil\"\n" \
            "From the text:\n");
    char long_text_test_20[] = (
            "Im Weltraum will die Menschheit ihre Zukunft sichern. Weil\n" \
            "die Erde nicht genug ist, sollen Menschen in den nächsten\n" \
            "Jahrzehnten regelmäßig ins All reisen – darunter\n" \
            "Astronautinnen, die auf Raumstationen forschen, und Touristen,\n" \
            " die den Mond umkreisen. Selbst eine Basis in Mondnähe soll\n" \
            "gebaut werden. Und vielleicht fliegt noch in diesem Jahrhundert\n" \
            "eine erste Delegation zum Mars.");
    printf("%s\n\n", long_text_test_20);
    read_index = 0;
    line = get_next_line(&read_index, long_text_test_20);
    printf("First line is: %s\n", line);
    printf("Should be true ->");
    if (streq(line, "Im Weltraum will die Menschheit ihre Zukunft sichern. Weil")) {
        printf("TRUE\n\n");
    } else {
        printf("FALSE\n\n");
    }
    free(line);
    line = get_next_line(&read_index, long_text_test_20);
    printf("Second line is: %s\n", line);
    printf("Should be true ->");
    if (streq(line, "die Erde nicht genug ist, sollen Menschen in den nächsten")) {
        printf("TRUE\n\n");
    } else {
        printf("FALSE\n\n");
    }
    free(line);



    printf("Test 21 (execute())\n" \
        "Calling the execute method between routers read and free.\n");
    routers_read("10_routers_10_edges");
    print_each();
    execute_commands("commands_10_routers.txt");
    printf("\n");
    print_each();
    routers_free();
    printf("\n\n");

    printf("Test 22 (write_routers())\n" \
        "Calling the execute method between routers read and free.\n");
    routers_read("10_routers_10_edges");
    print_each();
    // execute_commands("commands_10_routers.txt");
    routers_write("test_10_routers_10_edges");
    routers_free();
    routers_read("test_10_routers_10_edges");
    print_each();
    
    printf("\n\n");
}

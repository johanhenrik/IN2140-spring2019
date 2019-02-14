#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * A simple c-program that reads a file and write each line to the terminal.
 * What file to read is specified either from the terminal, when this
 * program is launched, or the user might write the file name inside the
 * program.
 */

int main(int argc, char *argv[]) {
    FILE *fs;
    // Max size of the file name is 20 characters.
    char file_name[20];
    if (argc > 1) {
        strncpy(file_name, argv[1], 20);
        //file_name = *argv[1];
    } else {
        char new_file_name[20];
        printf("File name is missing\nEnter the file name: ");
        scanf("%s", &new_file_name[0]);
        strncpy(file_name, new_file_name, 20);
    }
    printf("Received file name: %s\n", file_name);
    fs = fopen(file_name, "r");
    if (fs == NULL ) {
        perror("Error while opening file.\n");
        exit(EXIT_FAILURE);
    }
    // Trying to write file-content to the console!
    char file_content[1000];
    size_t read = fread(file_content, sizeof(char), 1000, fs);
    printf("Content of file is:\n%s\n\n", file_content);
    printf("I received %lu characters!\n", read);


}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * A simple c-program that reads a file and write each line to a new file with
 * name 'changed.txt'.
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
    // Trying to write file-content to the file 'changed lyrics'!
    char file_content[1000];
    size_t read = fread(file_content, sizeof(char), 1000, fs);
    // Rather than writing to the terminal, I write to a file.
    FILE *fd;
    fd = fopen("changed lyrics.txt", "w");
    if (fd == NULL) {
        perror("Error while opening file \"changed lyrics.txt\".\n");
        exit(EXIT_FAILURE);
    }
    size_t written = fwrite(file_content, sizeof(char), strlen(file_content), fd);
    printf("Wrote %lu char symbols to file \"changed lyrics.txt\".\n", written);


}
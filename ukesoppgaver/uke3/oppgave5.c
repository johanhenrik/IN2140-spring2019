#include <stdio.h>

/*
 * SYNOPSIS
 *      int printEveryOtherLineFromFile(char flpt[]);
 *
 * DESCRIPTION
 *      The printEveryOtherLineFromFile() function reads content from the file
 *      with relative file path flpt and prints every other line from the file
 *      to the terminal, starting with the first line of the file.
 * 
 * RETURN VALUE
 *      Upon successfully return, one (1) is returned, otherwise zero (0) is
 *      returned.
 */
int printEveryOtherLineFromFile(char flpt[]) {
    FILE *fs;
    fs = fopen(flpt, "r");
    if (fs == NULL ) {
        return 0;
    }
    // Trying to write file-content to the console!
    char file_content[10000];
    size_t read = fread(file_content, sizeof(char), 10000, fs);
    fclose(fs);
	// The file-content's length is defined from the fread function and its
	// type is an unsigned long. 
    unsigned long i;
    int writing = 1;
    for (i=0; i<read; i++) {
        char c = file_content[i];
        if (writing) {
            printf("%c", c);
        }
        if (c == '\n') {
            if (writing) {
                writing = 0;
            } else {
                writing = 1;
            }
        }   
    }
    return 1;
}

int STREQ(char s1[], char s2[]) {
	int index = 0;
	for (;;) {
			if (s1[index] == '\0' && s2[index] == '\0') {
			return 1;
		} else if (s1[index] != s2[index]) {
			return 0;
		}
		index++;
	}	
}

int main() {
	char user_input[40];
	char message[] = "This program reads a text file and prints every other "\
			"line to the terminal.\n"\
			"Exit with \"QUIT\"\n"
			"Enter file name - ";
	printf("%s", message);
	for (; ;) {
		scanf("%s", &user_input[0]);
		if (STREQ("QUIT", user_input)) {
			printf("bye\n");
			return 0;
		}
		else if (!printEveryOtherLineFromFile(user_input)) {
			printf("Could not open file with name %s\n\n", user_input);
			printf("%s", message);
		}
	}
}

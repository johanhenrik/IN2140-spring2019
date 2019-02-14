#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("This program requires a string parameter(\"\")\n");
        return 0;
    };
    int i;
    do {
        if (48 < *(argv[1] + i) && *(argv[1] + i) < 58) {
            printf("Has number! --");
       //     number[i] = *(argv[1] + i);
        } else {
            break;
        }
        printf("AS integer - %d --", *(argv[1] + i));
        printf("%c\n", *(argv[1] + i++));
    } while (*(argv[1] + i) != '\0');
    // printf("Our number - %s\n", number);
    return 0;
}
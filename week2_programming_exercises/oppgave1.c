#include <stdio.h>
#include <stdlib.h>

struct person {
    int age;
    char name[20];
};

struct person * person_create() {
    // struct* person my_person = (struct * person)malloc(sizeof(struct person));
    struct person* my_person = malloc(sizeof(struct person));
    my_person->age = 32;
    strncpy(my_person->name, "Johan Henrik", 22);
    // my_person->name = "Johan Henrik";
    return my_person;
}

int main() {
    struct person * my_person = person_create(10);
    printf("First person: age = %d\n", my_person->age);
    printf("First person: name = %s\n", my_person->name);
    return 0;
}
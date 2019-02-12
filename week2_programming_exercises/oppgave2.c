#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    int age;
    int pid;
    char name[20];
};

struct person * person_create(unsigned int count/*int age, char name[]*/) {
    // struct* person my_person = (struct * person)malloc(sizeof(struct person));
    struct person* my_person = malloc(count * sizeof(struct person));
    // (*(my_person+1)).age = 32;
    my_person[0].age = 32;
    strncpy(my_person[0].name, "Johan Henrik", 20);
    my_person[1].age = 21;
    strncpy(my_person[1].name, "Natalie", 20);
    my_person[2].age = 62;
    strncpy(my_person[2].name, "Ingunn", 20);
    my_person[3].age = 18;
    strncpy(my_person[3].name, "Aili", 20);
    return my_person;
}

int main() {
    int percou = 4;
    struct person * my_persons = person_create(percou);
    int i;
    for (i=0; i<percou; i++) {
        printf("Person [age - %d, name - %s]\n", my_persons[i].age,
            my_persons[i].name);
    }
    return 0;
}
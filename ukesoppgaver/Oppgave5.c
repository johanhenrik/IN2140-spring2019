#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO [ ] constructor (create_person) and destructor (free_person) 

/*
 * The person struct uses negative values for specifying that a an attribute
 * is set.
 */
struct person {
    char age;
    char name[20]; 
};

void person_set_age(struct person* p, char age);
void person_set_name(struct person* p, char name[]);

struct person* person_create() {
    struct person* my_person = malloc(sizeof(struct person));
    person_set_age(my_person, -1);
    my_person->name[0] = '\0';
    // person_set_name(my_person, "\0");
    return my_person;
}

int person_get_age(struct person* p) {
    return p->age;
}

char *person_get_name(struct person* p) {
    return p->name;
}

char person_has_age(struct person* p) {
    if (person_get_age(p) == -1) {
        return 0;    
    } else {
        return 1;
    }
}

char* person_information(struct person* p) {
    char info[40];
    sprintf(info, "Person[age=%d,name=%s]\n", p->age, p->name);
    printf("Printing info from the person string\n");
    printf("%s", info);
    char* new_info;
    return strncpy(new_info, info, 40);
}

char person_has_name(struct person* p) {
    // printf("Trying to print out value of a char pointer\n");
    // printf("--> %c", p->name[0]);
    if (p->name[0] == '\0') {
        return 0;    
    } else {
        return 1;
    }
}

void person_set_age(struct person * p, char age) {
    p->age = age;
}

void person_set_name(struct person * p, char name[]) {
    name = strncpy(p->name, name, 20);    
}

int main() {
    struct person * my_person = person_create();
    printf("Instantiated a person with age- %d and name %s.\n", 
        my_person->age, my_person->name);

    // Checking whether values are set.
    printf("Person [has age - ");
    if (person_has_age(my_person)) {
        printf("true");
    } else {
        printf("false");
    }
    printf("], [has name - ");
    if (person_has_name(my_person)) {
        printf("true");
    } else {
        printf("false");
    }
    printf("]\n");
    
    // Updating the values.
    person_set_age(my_person, 22);
    person_set_name(my_person, "Johan Henrik");

    // After values are set:
    printf("Now, values are [age - %d, name - %s]\n", person_get_age(my_person),
        person_get_name(my_person));

        // Checking whether values are set.
    printf("Person [has age - ");
    if (person_has_age(my_person)) {
        printf("true");
    } else {
        printf("false");
    }
    printf("], [has name - ");
    if (person_has_name(my_person)) {
        printf("true");
    } else {
        printf("false");
    }
    printf("]\n");
    printf("Printing the Person information:\n");
    printf("%s\n", person_information(my_person));
    return 0;
}
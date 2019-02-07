#include <stdlib.h>
#include <stdio.h>

struct node {
	struct node *next;

	char character;

};



/* Insert each character in line into a linked list and return
 *
 *  * a pointer to the first element.*/

struct node* create_list(char *line)
{
	// Iterative loop for creating local nodes, which stores characters.
	int string_index = 0;

	// Storing start node outside loop.
	struct node *first = malloc(sizeof(struct node));
	first->next = NULL;
	struct node *temp = first;
	string_index = 0;

	do {
		temp->character = *(line+string_index);
		temp->next = malloc(sizeof(struct node));
		temp = temp->next;
		temp->next = NULL;
		string_index++;
	} while (*(line+string_index) != '\0');


//		printf("Value of current pointer: %c\n", *(line+string_index));
//		printf("Value of current node: %c\n", *(line+string_index++));
	return first;



}



void print_list(struct node *list)
{
	while (list) {
		printf("Temporarily element: %c\n", list->character);
		list = list->next;
	}
}



/* Delete all nodes containing the character c */

struct node* delete_character(struct node *list, char c)
{



}





int main(int argc, char *argv[])
{
	struct node *list = create_list("abcd");
	print_list(list);
	if (argc < 2) {
		fprintf(stderr, "[USAGE]: ./%s <Line>\n", argv[0]);
		return 1;
	}

	// struct node *list = create_list(argv[1]);
	print_list(list);





	list = delete_character(list, 'a');

	printf("\nIf you delete all occurrences of the character 'a' you line becomes: ");

	print_list(list);



}

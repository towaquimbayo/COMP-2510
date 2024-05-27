#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char *type;
	int base;
	int limit;
	struct Node *next;
} Node;

struct Node *merge(struct Node *left, struct Node *right, int menuOption) {
	Node *temp = (Node*) malloc(sizeof(Node));
	Node *merged = temp;

	while (left != NULL && right != NULL) {
		if (left->base < right->base) {
			temp->next = left;
			left = left->next;
		} else {
			temp->next = right;
			right = right->next;
		}
		temp = temp->next;
	}

	while (left != NULL) {
		temp->next = left;
		left = left->next;
		temp = temp->next;
	}

	while (right != NULL) {
		temp->next = right;
		right = right->next;
		temp = temp->next;
	}
	return merged->next;
}

struct Node *middle(struct Node *head) {
	Node *slow = head;
	Node *fast = head->next;

	while (fast != NULL && fast->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

struct Node *mergeSort(struct Node *head, int menuOption) {
	if (head->next == NULL) {
		return head;
	}

	Node *mid = middle(head);
	Node *head2 = mid->next;
	mid->next = NULL;
	return merge(mergeSort(head, menuOption), mergeSort(head2, menuOption), menuOption);
}

void insertNode(char **type, int base, int limit, struct Node **head) {
	Node *temp = (Node*) malloc(sizeof(Node));
	temp->type = malloc(sizeof(char) * (strlen(*type) + 1));
	strcpy(temp->type, *type);
	temp->base = base;
	temp->limit = limit;
	temp->next = NULL;

	if (*head == NULL) {
		*head = temp;
		return;
	}

	Node *tail = *head;
	while (tail->next != NULL) {
		tail = tail->next;
	}
	tail->next = temp;
}

void printNodes(struct Node *head) {
	if (head == NULL) {
		printf("\n%s", "No nodes found.");
		exit(1);
	}

	int index = 1;
	printf("\n");
	while (head != NULL) {
		if (head->type[0] == 'H') {
			printf("Node %d: %s (Hole), base = %d, limit = %d\n", index, head->type, head->base, head->limit);
		} else {
			printf("Node %d: %s, base = %d, limit = %d\n", index, head->type, head->base, head->limit);
		}
		++index;
		head = head->next;
	}
}

int countNodes(FILE *fptr) {
	char c = (char) fgetc(fptr);
	int count = 0;
	int charactersPerLine = 0;
	while (c != EOF) {
		if (c != ' ' && c != '\n') {
			charactersPerLine++;
		}

		if (c == '\n' && charactersPerLine > 1) {
			++count;
			charactersPerLine = 0;
		}

		c = (char) fgetc(fptr);

		if (c == EOF && charactersPerLine > 1) {
			++count;
			charactersPerLine = 0;
		}
	}

	if (count == 0) {
		printf("\n%s", "Error: No nodes in the file.");
		exit(1);
	}

	rewind(fptr);
	return count;
}

void mergeFreeBlocks(struct Node **node) {
	Node *head = *node;

	while (*node != NULL) {
		if ((*node)->type[0] == 'H' && (*node)->next != NULL && (*node)->next->type[0] == 'H') {
			(*node)->limit += (*node)->next->limit;
			Node *nextHole = (*node)->next->next;
			free((*node)->next);
			(*node)->next = nextHole;
		} else {
			*node = (*node)->next;
		}
	}

	*node = head;
}

struct Node *getTail(struct Node *head) {
	Node *tail = head;
	while (tail->next != NULL) {
		tail = tail->next;
	}
	return tail;
}

void reassignBase(struct Node **node) {
	Node *head = *node;

	int newBase = 0;
	while (*node != NULL) {
		(*node)->base = newBase;
		newBase += (*node)->limit;
		*node = (*node)->next;
	}

	*node = head;
}

struct Node *compaction(struct Node **node) {
	mergeFreeBlocks(&(*node));
	Node *head = NULL;
	Node *tail = getTail(*node);
	int foundHead = 0;

	if ((*node)->type[0] == 'H' && (*node)->next == NULL) { // only 1 big hole and no processors
		return (*node);
	}

	Node *prevNode = NULL;
	while ((*node) != NULL) {
		if (foundHead == 0 && (*node)->type[0] == 'P') {
			head = (*node);
			foundHead = 1;
			prevNode = (*node);
			(*node) = (*node)->next;
		} else if ((*node)->type[0] == 'H' && (*node)->next != NULL) {
			if ((*node)->next->type[0] == 'H') {
				mergeFreeBlocks(&head);
			} else {
				Node *hole = (*node);
				if (prevNode != NULL) {
					prevNode->next = (*node)->next;
				}
				(*node) = (*node)->next;

				tail->next = hole;
				tail = tail->next;
				tail->next = NULL;
			}
		} else {
			prevNode = (*node);
			(*node) = (*node)->next;
		}
	}
	reassignBase(&head);
	return head;
}

int main(int argc, char **argv) {
	int menuOption = 0;
	Node *head = NULL;

	while (menuOption != 5) {
		printf("\n%s\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n%s",
		       "Choose an option from the menu:",
		       "1. load an input file",
		       "2. merge holes",
		       "3. compact memory",
		       "4. print memory view",
		       "5. Exit the program",
			   "Enter your option:");

		scanf("%d", &menuOption);

		if (menuOption > 5 || menuOption < 1) {
			printf("\n%s\n", "Invalid option.");
		}

		switch (menuOption) {
			case 1: // load an input file
				printf("%s", "Type the file name:");
				char *inputFilename = (char *) malloc(sizeof(char) * 100);
				scanf("%s", inputFilename);
				inputFilename = realloc(inputFilename, sizeof(char) * (strlen(inputFilename) + 1));
				inputFilename[strlen(inputFilename)] = '\0';

				FILE *fp = fopen(inputFilename, "r");
				if (fp == NULL) {
					printf("\n%s", "Error: No file found.");
					exit(1);
				} else if (fgetc(fp) == EOF) {
					printf("\n%s", "Error: Nothing in file.");
					exit(1);
				}
				rewind(fp);

				int numNodes = countNodes(fp);

				for (int i = 0; i < numNodes; i++) {
					char *type = (char*) malloc(sizeof(char) * 3);
					int base, limit;

					int scanned = fscanf(fp, "%s %d %d", type, &base, &limit);

					if (scanned != 3) {
						printf("%s %d", "Error: Missing or extra fields on line:", (i + 1));
						exit(1);
					} else if (type[0] != 'H' && type[0] != 'P') {
						printf("%s %d", "Error: Type must be either Process (P) or Hole (H) on line:", (i + 1));
						exit(1);
					} else if (base < 0) {
						printf("%s %d", "Error: Base must be positive value on line:", (i + 1));
						exit(1);
					} else if (limit < 1) {
						printf("%s %d", "Error: Limit must greater than 0 on line:", (i + 1));
					}

					insertNode(&type, base, limit, &head);
				}
				head = mergeSort(head, menuOption);
				reassignBase(&head);
				printf("%s\n", "Operation successful!");
				break;
			case 2:
				mergeFreeBlocks(&head);
				printf("%s\n", "Operation successful!");
				break;
			case 3:
				head = compaction(&head);
				printf("%s\n", "operation successful");
				break;
			case 4:
				printNodes(head);
				break;
			case 5:
				printf("%s", "Exiting the program");
				exit(0);
			default:;
		}
	}
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Array {
	void *data;
	struct Array *next;
} Array;

void fillArray(struct Array **head, void *data, size_t nBytes) {
	Array *temp = (Array*) malloc(sizeof(Array));
	temp->data = malloc(nBytes);
	memcpy(temp->data, data, sizeof(void*));
	temp->next = NULL;

	if (*head == NULL) {
		*head = temp;
		return;
	}

	Array *tail = *head;
	while (tail->next != NULL) {
		tail = tail->next;
	}
	tail->next = temp;
}

void assignLeft(struct Array **temp, struct Array **left) {
	(*temp)->next = *left;
	(*left) = (*left)->next;
}

void assignRight(struct Array **temp, struct Array **right) {
	(*temp)->next = *right;
	(*right) = (*right)->next;
}

struct Array *merge(struct Array *left, struct Array *right, int dataType) {
	Array *temp = (Array*) malloc(sizeof(Array));
	Array *merged = temp;

	while (left != NULL && right != NULL) {
		switch (dataType) {
			case 1:
				if (atoi(left->data) > atoi(right->data)) {
					assignLeft(&temp, &left);
				} else {
					assignRight(&temp, &right);
				}
				break;
			case 2: case 3:
				if (atof(left->data) > atof(right->data)) {
					assignLeft(&temp, &left);
				} else {
					assignRight(&temp, &right);
				}
				break;
			case 4:
				if (*(char *) left->data > *(char *) right->data) {
					assignLeft(&temp, &left);
				} else {
					assignRight(&temp, &right);
				}
				break;
			default:;
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

struct Array *middle(struct Array *head) {
	Array *slow = head;
	Array *fast = head->next;

	while (fast != NULL && fast->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

struct Array *mergeSort(struct Array *head, int dataType) {
	if (head->next == NULL) {
		return head;
	}
	Array *mid = middle(head);
	Array *head2 = mid->next;
	mid->next = NULL;
	return merge(mergeSort(head, dataType), mergeSort(head2, dataType), dataType);
}

void printArray(struct Array *head, int dataType) {
	switch (dataType) {
		case 1:
			while (head != NULL) {
				printf("%d ", atoi(head->data));
				head = head->next;
			}
			break;
		case 2:
			while (head != NULL) {
				printf("%f ", atof(head->data));
				head = head->next;
			}
			break;
		case 3:
			while (head != NULL) {
				printf("%e ", atof(head->data));
				head = head->next;
			}
			break;
		case 4:
			while (head != NULL) {
				printf("%c ", *(char *) head->data);
				head = head->next;
			}
			break;
		default:;
	}
	printf("\n");
}

void getIndex(struct Array *head, int index, int length, int dataType) {
	if (length <= index) {
		printf("%s\n", "Index is out of bounds.");
		return;
	} else {
		for (int i = 0; i < index; i++) {
			head = head->next;
		}

		switch (dataType) {
			case 1:
				printf("%s %d %s %d\n", "Index", index, "of array is:", atoi(head->data));
				break;
			case 2: case 3:
				printf("%s %d %s %f\n", "Index", index, "of array is:", atof(head->data));
				break;
			case 4:
				printf("%s %d %s %c\n", "Index", index, "of array is:", *(char *) head->data);
				break;
			default:;
		}
	}
}

int getLength(struct Array *head) {
	int length = 0;
	while (head != NULL) {
		length++;
		head = head->next;
	}
	return length;
}

int main (int argc, char **argv) {
	int dataTypeOption = 0;
	int menuOption = 0;

	printf("%s", "What data type do you want?");
	printf("\n%s\n%s\n%s\n%s\n", "1) Int", "2) Float", "3) Scientific", "4) Character");
	printf("%s", "Enter your option here:");

	if (scanf("%d", &dataTypeOption) > 1) {
		printf("%s\n", "More than 1 value was inputted.");
		exit(1);
	} else if (dataTypeOption < 1 || dataTypeOption > 4) {
		printf("%s\n", "Invalid option selected.");
		exit(1);
	}

	Array *head = NULL;

	while (menuOption != 4) {
		printf("\n%s", "Enter one of the options:");
		printf("\n%s\n%s\n%s\n%s\n", "1) Input the data", "2) Sort the array", "3) Index the array", "4) Exit the program");
		printf("\n%s", "Enter your option here:");

		if (scanf("%d", &menuOption) > 1) {
			printf("%s", "More than 1 value was inputted.");
		} else if (menuOption < 1 || menuOption > 4) {
			printf("%s", "Invalid option selected.");
		}

		switch (menuOption) {
			case 1: // Input the Data
				printf("\n%s", "Input your data:");
				char *data = (char *) malloc(sizeof(char) * 100);
				scanf("%s", data);
				data = realloc(data, sizeof(char) * (strlen(data) + 1));
				data[strlen(data)] = '\0';

				switch (dataTypeOption) {
					case 1:
						fillArray(&head, data, sizeof(int));
						break;
					case 2:
						fillArray(&head, data, sizeof(float));
						break;
					case 3:
						fillArray(&head, data, sizeof(double));
						break;
					case 4:
						fillArray(&head, data, sizeof(char));
						break;
					default:;
				}
				printArray(head, dataTypeOption);
				free(data);
				break;
			case 2: // Sort the array
				printf("\n%s", "Before Sort:\n");
				printArray(head, dataTypeOption);

				head = mergeSort(head, dataTypeOption);

				printf("\n%s", "After Sort:\n");
				printArray(head, dataTypeOption);
				break;
			case 3:
				printf("\n%s", "Please input the index:");
				int index;
				scanf("%d", &index);
				getIndex(head, index, getLength(head), dataTypeOption);
				break;
			case 4:
				printf("\n%s", "Exiting the program");
				free(head);
				exit(0);
			default: ;
		}
	}
	free(head);
	return 0;
}
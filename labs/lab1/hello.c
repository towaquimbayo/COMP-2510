#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//int gcd(int a, int b) {
//	if (a == b) {
//		return a;
//	} else {
//		if (a > b) {
//			return (a - b, b);
//		} else {
//			return (a, b - a);
//		}
//	}
//}

int power(int x, int exp) {
	if (exp == 0) {
		return 1;
	} else {
		return x * power(x, exp - 1);
	}
}

int factorial(int x) {
	if (x == 0) {
		return 1;
	} else {
		return x * factorial(x - 1);
	}
}

int fibonacci(int x) {
	if (x == 0) {
		return 0;
	} else if (x == 1) {
		return 1;
	} else {
		return fibonacci(x - 1) + fibonacci(x - 2);
	}
}

// Stack
typedef struct Node {
	int data;
	struct Node *next;
} Node;

struct Node *head = NULL;

void push(int x) {
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->data = x;
	newNode->next = head;
	head = newNode;
}

int pop() {
	struct Node *temp;
	int data = 0;
	if (head == NULL) {
		printf("%s", "Stack is empty");
		exit(1);
	} else {
		data = head->data;
		temp = head;
		head = head->next;
		free(temp);
	}
	return data;
}

int main() {
	//printf("%d", power(4, 2));
	//printf("%d", factorial(0));
	//printf("%d", fibonacci(6));

	push(50);
	push(4);
	push(95);
	push(23);
	push(8);

	for (int i = 0; i < 5; i++) {
		printf("Popped: %d\n", pop());
	}

	return 0;
}
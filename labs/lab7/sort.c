/**
 * File: sort.c
 *
 * Author: Towa Quimbayo
 * Date: November 17, 2022
 * Course: COMP 2510 - Procedural Programming
 *
 * Summary of File:
 *
 * This file merge sorts the Student linked list by
 * GPA > TOEFL > First Name > Last Name.
 */
#include "file_handler.h"
#include "sort.h"

/**
 * Inserts the values to the Structs. If head is null then set next to NULL.
 *
 * @param firstName for Student first name
 * @param lastName for Student last name
 * @param gpa for Student gpa
 * @param status for Student status
 * @param toefl for Student toefl
 * @param head for Student currently being filled
 */
void insert(char **firstName, char **lastName, float gpa, char status, int toefl, Students **head) {
	if (*head == NULL) {
		*head = (Students*)malloc(sizeof(Students));
		(*head)->firstName = malloc(sizeof(char) * (strlen(*firstName) + 1));
		strcpy((*head)->firstName,*firstName);
		(*head)->lastName = malloc(sizeof(char) * (strlen(*firstName) + 1));
		strcpy((*head)->lastName,*lastName);
		(*head)->gpa = gpa;
		(*head)->status = status;
		if (status == 'D') {
			(*head)->toefl = -1;
		} else {
			(*head)->toefl = toefl;
		}
		(*head)->next = NULL;
		return;
	}
	Students* temp = (Students*)malloc(sizeof(Students));
	temp->firstName = malloc(sizeof(char) * (strlen(*firstName) + 1));
	strcpy(temp->firstName,(*head)->firstName);
	temp->lastName = malloc(sizeof(char) * (strlen(*firstName) + 1));
	strcpy(temp->lastName,(*head)->lastName);
	temp->gpa = (*head)->gpa;
	temp->status = (*head)->status;
	temp->toefl = (*head)->toefl;
	temp->next = (*head)->next;
	(*head)->firstName = malloc(sizeof(char) * (strlen(*firstName) + 1));
	strcpy((*head)->firstName,*firstName);
	(*head)->lastName = malloc(sizeof(char) * (strlen(*firstName) + 1));
	strcpy((*head)->lastName,*lastName);
	(*head)->gpa = gpa;
	(*head)->status = status;
	if (status == 'D') {
		(*head)->toefl = 0;
	} else {
		(*head)->toefl = toefl;
	}
	(*head)->next = temp;
}

/**
 * Merge the left and right lists by sorting the list and
 * linking in order of the condition.
 *
 * @param left for left side of the linked list
 * @param right for right side of the linked list
 * @return the merged list that combines the sorted left and right lists
 */
struct Students *merge(struct Students *left, struct Students *right) {
	Students *temp = (Students*)malloc(sizeof(Students));
	Students *merged = temp;

	while (left != NULL && right != NULL) {
		if ((left->gpa > right->gpa)
			|| ((left->gpa == right->gpa) && ((left->toefl > right->toefl)
			|| ((left->toefl == right->toefl) && ((strcmp(left->firstName, right->firstName) < 0)
		    || ((strcmp(left->firstName, right->firstName) == 0) && (strcmp(left->lastName, right->lastName) == 0))))))) {
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

/**
 * Find the mid point of the list.
 *
 * @param head for the head of the linked list
 * @return mid point of the list
 */
struct Students *middle(Students *head) {
	Students *slow = head;
	Students *fast = head->next;

	while (fast != NULL && fast->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

/**
 * Merge sort the linked list by finding the mid point
 * and merge the left and right list after being sorted.
 *
 * @param head for the head of the linked list
 * @return merged linked list that is sorted
 */
struct Students *mergeSort(struct Students *head) {
	if (head->next == NULL) {
		return head;
	}
	Students *mid = middle(head);
	Students *head2 = mid->next;
	mid->next = NULL;
	return merge(mergeSort(head), mergeSort(head2));
}
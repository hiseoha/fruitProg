#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[100];
} element;

typedef struct ListNode {
	element data;
	struct ListNode* link;
} ListNode;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	return;
}

ListNode* insert_first(ListNode* head, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

ListNode* insert(ListNode* head, ListNode* pre, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;
	pre->link = p;
	return head;
}

ListNode* delete_first(ListNode* head) {
	ListNode* removed;
	if (head == NULL)
		return NULL;
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

ListNode* delete(ListNode* head, ListNode* pre)
{
	ListNode* removed;
    removed = pre->link;
    pre->link = removed->link;
    removed->link = NULL;
    return head;
}

ListNode* search_list(ListNode* head, element value) {
	ListNode* p = head;
	while (p != NULL) {
		if (strcmp(p->data.name, value.name) == 0)
			return p;
		p = p->link;
	}
	return NULL;
}

void print_list(ListNode* head) {
	printf("\nfruit list: ");
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%s->", p->data.name);
	printf("NULL \n");
}

void print_deletedList(ListNode* head) {
	printf("List of deleted fruits: ");
	if (head == NULL) {
		printf("NULL\n");
		return;
	}
	ListNode* p;
	for (p = head; p->link != NULL; p = p->link)
		printf("%s->", p->data.name);
	printf("%s->NULL\n", p->data.name);
}

int main(void)
{
	ListNode* head = NULL;
	ListNode* deletedList = NULL;
	int choice;
	element item;

	element fruitList[] = {
	{"Mango"}, {"Orange"}, {"Apple"}, {"Grape"}, {"Cherry"},
	{"Plum"}, {"Guava"}, {"Raspberry"}, {"Banana"}, {"Peach"}
	};

	int fruitNum = sizeof(fruitList) / sizeof(element);

	for (int i = 0; i < fruitNum; i++) {
		if (head == NULL) {
			head = insert_first(head, fruitList[i]);
		}
		else {
			ListNode* current = head;
			while (current->link != NULL) {
				current = current->link;
			}
			insert(head, current, fruitList[i]);
		}
	}

	while (1) {
		printf("Menu\n");
		printf("1. Insert new fruit\n");
		printf("2. Delete a fruit\n");
		printf("3. Print the deleted list\n");
		printf("4. Exit\n");
		printf("Enter the menu: ");
		scanf_s("%d", &choice);

		if (choice == 1) {
			printf("Fruit name to add: ");
			scanf_s("%s", item.name, 100);
			if (search_list(head, item) != NULL) {
				printf("%s already exists in the list.\n", item.name);
			}
			else {
				ListNode* current = head;
				while (current->link != NULL) {
					current = current->link;
				}
				head = insert(head, current, item);
				printf("%s has been added.\n", item.name);
			}
			print_list(head);
		}
		else if (choice == 2) {
			printf("Fruit name to delete: ");
			scanf_s("%s", item.name, 100);
			ListNode* found = search_list(head, item);
			if (found != NULL) {
				if (found == head) {
					head = delete_first(head);
				}
				else {
					ListNode* prev = head;
					while (prev->link != found)
						prev = prev->link;
					head = delete(head, prev);
				}
				if (deletedList == NULL) {
					deletedList = insert_first(deletedList, found->data);
				}
				else {
					ListNode* current = deletedList;
					while (current->link != NULL)
						current = current->link;
					insert(deletedList, current, found->data);
				}
				printf("%s has been deleted.\n", item.name);
			}
			else {
				printf("%s is not in the list.\n", item.name);
			}
			print_list(head);
		}
		else if (choice == 3) {
			print_deletedList(deletedList);
			print_list(head);
		} 
		else if (choice == 4) {
			printf("Exit the program.\n");
			break;
		}
		else {
			printf("Invalid Menu. Please select again. \n");
		}
	}
	return 0;
}
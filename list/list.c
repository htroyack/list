#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>  

struct list {
	int value;
	struct list* next;
};

struct list* list_new_node(int value) {
	struct list* list_new_node = malloc(sizeof(struct list));
	if (list_new_node) {
		list_new_node->value = value;
		list_new_node->next = NULL;
	}

	return list_new_node;
}

struct list* list_add_iterative(struct list* list, int value) {
	while (list->next)
		list = list->next;

	list->next = list_new_node(value);

	return list;
}

struct list* list_add_recursive(struct list* list, int value) {
	if (list->next)
		return list_add_recursive(list->next, value);

	list->next = list_new_node(value);

	return list->next;
}

void list_delete_iterative(struct list* list) {
	struct list* next;
	while (list) {
		next = list->next;
		free(list);
		list = next;
	}
}

void list_delete_recursive(struct list* list) {
	if (list->next)
		list_delete_iterative(list->next);

	free(list);
}

void list_print_iterative(struct list* list) {
	while (list) {
		printf("%8x -> ", list->value);
		list = list->next;
	}
	putchar('\n');
}

void list_print_recursive(struct list* list) {
	if (list) {
		printf("%08x -> ", list->value);
		list_print_recursive(list->next);
	}
	else {
		putchar('\n');
	}
}

struct list* list_reverse_iterative(struct list* list) {
	struct list* following = NULL;
	struct list* previous = NULL;

	while (list) {
		following = list->next;
		list->next = previous;
		previous = list;
		list = following;
	}

	return previous;
}

struct list* list_reverse_recursive(struct list* list, struct list* previous) {
	if (!list)
		return previous;

	struct list* following = list->next;
	list->next = previous;

	return list_reverse_recursive(following, list);
}

void iterate(struct list* list) {
	list = list_new_node(0);
	for (int i = 1; i < 10; i++) {
		list_add_iterative(list, i*8);
	}
	list_print_iterative(list);
	list = list_reverse_iterative(list);
	list_print_iterative(list);
	list_delete_iterative(list);
}

void recurse(struct list* list) {
	list = list_new_node(0);
	for (int i = 1; i < 10; i++) {
		list_add_recursive(list, i*8);
	}
	list_print_recursive(list);
	list = list_reverse_recursive(list, NULL);
	list_print_recursive(list);
	list_delete_recursive(list);
}

int main() {
	// _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	struct list* list = NULL;
	
	iterate(list);
	recurse(list);

	_CrtDumpMemoryLeaks();
	return 0;
}

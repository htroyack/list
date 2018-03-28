#include <stdio.h>
#include <stdlib.h>

struct list {
	int value;
	struct list* next;
};

struct list** list_get_tail(struct list** list) {
	while (*list)
		list = &(*list)->next;

	return list;
}

struct list* list_add(struct list** list, int value) {
	list = list_get_tail(list);
	*list = malloc(sizeof(struct list));
	if (*list) {
		(*list)->value = value;
		(*list)->next = NULL;
	}
	return *list;
}

int main() {

	struct list* list = NULL;

	list_add(&list, 42);
	list_add(&list, 0xCafeBabe);

	return 0;
}

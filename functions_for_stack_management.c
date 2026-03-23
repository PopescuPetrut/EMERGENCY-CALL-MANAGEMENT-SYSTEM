#include "emergency_call.h"

void push(list *lista, void *data)
{
	add_nth_node(lista, lista->size, data);
}

void pop(list *lista)
{
	if (lista->size == 0) {
		fprintf(stderr, "Poping an empty stack");
		return;
	}
	remove_nth_node(lista, lista->size - 1);
}

node *top(list *lista)
{
	if (lista->size == 0) {
		fprintf(stderr, "Empty stack");
		return NULL;
	}

	return get_nth_element(lista, lista->size - 1);
}

int stack_isempty(list *lista)
{
	if (lista->size == 0) {
		return 1;
	} else {
		return 0;
	}
}
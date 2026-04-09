// POPESCU PETRUT - ALIN 312CA

#include "emergency_call.h"

// add an element in the stack
void push(list *lista, void *data)
{
	add_nth_node(lista, lista->size, data);
}

// remove an element from the stack
void pop(list *lista)
{
	if (lista->size == 0) {
		fprintf(stderr, "Popping an empty stack");
		return;
	}
	remove_nth_node(lista, lista->size - 1);
}

// returns the element placed on the top of the stack
node *top(list *lista)
{
	if (lista->size == 0) {
		fprintf(stderr, "Empty stack");
		return NULL;
	}

	return get_nth_element(lista, lista->size - 1);
}

// verifies if the stack is empty
int stack_isempty(list *lista)
{
	if (lista->size == 0) {
		return 1;
	} else {
		return 0;
	}
}
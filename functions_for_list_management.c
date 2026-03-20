#include "emergency_call.h"

list *create_list(DATA_TYPE a)
{
	list *lista = malloc(sizeof(list));
	if(!lista) {
		fprintf(stderr, "Allocation error for list");
		return NULL;
	}

	lista->type = a;
	lista->size = 0;
	lista->head = NULL;
	lista->tail = NULL;
	return lista;
}

void add_nth_node(list *lista, int pos, void *data)
{
	if (!lista) {
		return;
	}

	node *new_node = malloc(sizeof(node));
	if(!new_node) {
		fprintf(stderr, "Allocation error for node");
		return;
	}

	if (lista->type == INCIDENT) {
		new_node->data = (incident *)malloc(sizeof(incident));
		memcpy(new_node->data, data, sizeof(incident));
	} else if (lista->type == INTERVENTION) {
		new_node->data = (intervention *)malloc(sizeof(intervention));
		memcpy(new_node->data, data, sizeof(intervention));
	}

	if (pos == 0) {
		new_node->next = lista->head;
		new_node->prev = lista->tail;
		lista->head->prev = new_node;
		lista->head = new_node;
	}

	if (pos > lista->size) {
		pos = lista->size;
	}

	node *it = lista->head;
	for (int i = 0; i < pos - 1; i++) {
		it = it->next;
	}

	new_node->prev = it;
	it->next->prev = new_node;
	new_node->next = it->next;
	it->next = new_node;
}


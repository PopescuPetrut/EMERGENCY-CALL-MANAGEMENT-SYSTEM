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
	} else if (lista->type == UNITS) {
		new_node->data = (unit *)malloc(sizeof(unit));
		memcpy(new_node->data, data, sizeof(unit));
	} else if (lista->type == POINTERS) {
		new_node->data = data;
	}

	node *it = lista->head;
	if (pos >= lista->size) {
		pos = lista->size;
	}

	if (pos == 0 && lista->size == 0) {
		lista->head = new_node;
		lista->tail = new_node;
	} else if (pos == 0) {
		new_node->next = lista->head;
		new_node->prev = lista->tail;
		lista->head->prev = new_node;
		lista->head = new_node;
	} else if (pos == lista->size) {
		new_node->prev = lista->tail;
		new_node->next = lista->head;
		lista->tail->next = new_node;
		lista->head->prev = new_node;
		lista->tail = new_node;
	} else {
		for (int i = 0; i < pos - 1; i++) {
			it = it->next;
		}

		new_node->prev = it;
		it->next->prev = new_node;
		new_node->next = it->next;
		it->next = new_node;
	}

	lista->size++;
}

void remove_nth_node(list *lista, int pos)
{
	if (!lista || !lista->head) {
		return;
	}

	node *remove;
	if (pos >= lista->size) {
		pos = lista->size - 1;
	}

	if (pos == 0) {
		remove = lista->head;
		lista->head = remove->next;
		lista->head->prev = lista->tail;
		lista->tail->next = lista->head;
	} else if (pos == lista->size - 1) {
		remove = lista->tail;
		lista->tail = lista->tail->prev;
		lista->tail->next = lista->head;
		lista->head->prev = lista->tail;
	} else {
		remove = lista->head;
		for (int i = 0; i < pos; i++) {
			remove = remove->next;
		}

		remove->prev->next = remove->next;
		remove->next->prev = remove->prev;
	}

	if (lista->type != POINTERS) {
		free(remove->data);
	}
	free(remove);
	lista->size--;
}

node *get_nth_element(list *lista, int pos)
{
	if (!lista || !lista->head) {
		return NULL;
	}

	node *it = lista->head;
	if (pos >= lista->size) {
		pos = lista->size - 1;
	}
	for (int i = 0; i < pos; i++) {
		it = it->next;
	} 

	return it;
}

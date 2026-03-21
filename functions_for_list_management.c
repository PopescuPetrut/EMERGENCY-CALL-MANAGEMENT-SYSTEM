#include "emergency_call.h"

list *create_list(DATA_TYPE a)
{
	list *lista = malloc(sizeof(list));
	if(!lista) {
		fprintf(stderr, "Allocation error for list");
		return NULL;
	}

	node *sentinel = malloc(sizeof(node));
	if (!sentinel) {
		fprintf(stderr, "Sentinel can not be allocated");
		return NULL;
	}

	sentinel->next = sentinel;
	sentinel->prev = sentinel;
	sentinel->data = NULL;

	lista->type = a;
	lista->size = 0;
	lista->head = sentinel;
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
		int description_len = strlen(((incident *)data)->description); 
		((incident *)new_node->data)->description = (char *)malloc(sizeof(char) * description_len + 1);
		strcpy(((incident *)(new_node->data))->description, ((incident *)data)->description);
		((incident *)new_node->data)->ID = ((incident *)data)->ID;
		strcpy(((incident *)(new_node->data))->priority, ((incident *)data)->priority);
		strcpy(((incident *)(new_node->data))->status, ((incident *)data)->status);
	} else if (lista->type == INTERVENTION) {
		new_node->data = (intervention *)malloc(sizeof(intervention));
		memcpy(new_node->data, data, sizeof(intervention));
	} else if (lista->type == UNITS) {
		new_node->data = (unit *)malloc(sizeof(unit));
		memcpy(new_node->data, data, sizeof(unit));
	} else if (lista->type == POINTERS) {
		new_node->data = data;
	}

	node *it = lista->head->next;
	if (pos >= lista->size) {
		pos = lista->size;
	}

	for (int i = 0; i < pos - 1; i++) {
		it = it->next;
	}

	new_node->prev = it;
	it->next->prev = new_node;
	new_node->next = it->next;
	it->next = new_node;
	
	lista->size++;
}

void remove_nth_node(list *lista, int pos)
{
	if (!lista || !lista->head->next) {
		return;
	}

	node *remove;
	if (pos >= lista->size) {
		pos = lista->size - 1;
	}

	remove = lista->head->next;
	for (int i = 0; i < pos; i++) {
		remove = remove->next;
	}

	remove->prev->next = remove->next;
	remove->next->prev = remove->prev;
	
	if (lista->type != POINTERS) {
		free(remove->data);
	}
	free(remove);
	lista->size--;
}

node *get_nth_element(list *lista, int pos)
{
	if (!lista || !lista->head->next) {
		return NULL;
	}

	node *it = lista->head->next;
	if (pos >= lista->size) {
		pos = lista->size - 1;
	}
	for (int i = 0; i < pos; i++) {
		it = it->next;
	} 

	return it;
}

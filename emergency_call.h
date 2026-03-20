#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int ID;
	char type;
	int availability;
} unit;

typedef struct {
	int ID;
	char priority[7];
	char *description;
	char status[11];
} incident;

typedef struct {
	unit *unit;
	incident *incident;
} intervention;

typedef struct {
	unit *units;
	incident *incidents;
	intervention *interventions;
} call_system;

typedef struct {
	void *data;
	struct node *next, *prev;
} node;

typedef struct {
	int size;
	int data_type;
	node *head;
	node *tail;
} list;
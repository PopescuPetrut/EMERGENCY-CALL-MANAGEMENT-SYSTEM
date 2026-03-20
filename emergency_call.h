#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct unit {
	int ID;
	char type;
	int availability;
};

typedef struct incident {
	int ID;
	char priority[7];
	char *description;
	char status[11];
};

typedef struct intervention {
	unit *unit;
	incident *incident;
};

typedef struct system {
	unit *units;
	incident *incidents;
	intervention *interventions;
};

typedef struct node {
	void *data;
	node *next, *prev;
};

typedef struct list {
	int size;
	int data_type;
	node *head;
	node *tail;
};
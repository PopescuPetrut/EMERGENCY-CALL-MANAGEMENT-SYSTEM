#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct unit{
	int ID;
	char type;
	int availability;
} unit;

typedef struct incident{
	int ID;
	char priority[7];
	char *description;
	char status[11];
} incident;

typedef struct intervention{
	unit *unit;
	incident *incident;
} intervention;

typedef struct call_system{
	unit *units;
	incident *incidents;
	intervention *interventions;
} call_system;

typedef struct node{
	void *data;
	struct node *next, *prev;
} node;

typedef enum DATA_TYPE{
	INCIDENT,
	INTERVENTION
} DATA_TYPE;

typedef struct list{
	int size;
	DATA_TYPE type;
	node *head;
	node *tail;
} list;

void command_processing(char *command, unit *units);
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
	void *data;
	struct node *next, *prev;
} node;

typedef enum DATA_TYPE{
	INCIDENT,
	INTERVENTION,
	UNITS,
	POINTERS
} DATA_TYPE;

typedef struct list{
	int size;
	DATA_TYPE type;
	node *head;
	node *tail;
} list;

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
	unit *unit_to_deploy;
	incident *incident_to_solve;
} intervention;

typedef struct call_system{
	list *units;
	list *incidents;
	list *interventions;
	list *queue_high;
	list *queue_medium;
	list *queue_low;
	list *queue_available_units;
	list *stack_interventions;
} call_system;

void command_processing(char *command, call_system *system);
list *create_list(DATA_TYPE a);
void add_nth_node(list *lista, int pos, void *data);
void remove_nth_node(list *lista, int pos);
node *get_nth_element(list *lista, int pos);
void enqueue(list *queue, void *data);
void dequeue(list *queue);
node *front(list *queue);
int queue_isempty(list *queue);
void free_list(list **lista);
void free_system(call_system **system);
void push(list *lista, void *data);
void pop(list *lista);
node *top(list *lista);
int stack_isempty(list *lista);
void priority_enqueue(list *queue, void *data);

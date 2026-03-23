#include "emergency_call.h"

void enqueue(list *queue, void *data)
{
	add_nth_node(queue, queue->size, data);
}

void priority_enqueue(list *queue, void *data)
{
	add_nth_node(queue, 0, data);
}

void dequeue(list *queue)
{
	if (queue->size) {
		remove_nth_node(queue, 0);
	} else {
		fprintf(stderr, "Dequeueing an empty queue");
		return;
	}
}

node *front(list *queue)
{
	if (queue->size) {
		return get_nth_element(queue, 0);
	} else {
		fprintf(stderr, "Accessing an invalid position in queue");
		return NULL;
	}
}

int queue_isempty(list *queue)
{
	if (queue->size == 0) {
		return 1;
	} else {
		return 0;
	}
}
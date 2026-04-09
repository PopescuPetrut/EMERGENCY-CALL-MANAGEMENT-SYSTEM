// POPESCU PETRUT - ALIN 312CA

#include "emergency_call.h"

// add an element in the queue
void enqueue(list *queue, void *data)
{
	add_nth_node(queue, queue->size, data);
}

// add an element on the first position in the queue
void priority_enqueue(list *queue, void *data)
{
	add_nth_node(queue, 0, data);
}

// remove an element from the queue
void dequeue(list *queue)
{
	if (queue->size) {
		remove_nth_node(queue, 0);
	} else {
		fprintf(stderr, "Dequeueing an empty queue");
		return;
	}
}

// returns a pointer to the first element of the queue
node *front(list *queue)
{
	if (queue->size) {
		return get_nth_element(queue, 0);
	} else {
		fprintf(stderr, "Accessing an invalid position in queue");
		return NULL;
	}
}

// verifies if the queue is empty
int queue_isempty(list *queue)
{
	if (queue->size == 0) {
		return 1;
	} else {
		return 0;
	}
}
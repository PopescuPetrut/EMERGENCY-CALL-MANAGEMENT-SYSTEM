#include "emergency_call.h"

int main(void)
{
	call_system *system = malloc(sizeof(call_system));
	if (!system) {
		fprintf(stderr, "System memory allocation faield");
		return -1;
	}
	system->incidents = create_list(INCIDENT);
	system->interventions = create_list(INTERVENTION);
	system->units = create_list(UNITS);
	system->queue_high = create_list(POINTERS);
	system->queue_medium = create_list(POINTERS);
	system->queue_low = create_list(POINTERS);
	system->queue_available_units = create_list(POINTERS);
	system->stack_interventions = create_list(POINTERS);
	int nr_units;
	FILE *in = fopen("tema1.in", "rt");

	fscanf(in, "%d", &nr_units);
	getc(in);
	for (int i = 0; i < nr_units; i++) {
		unit aux;
		fscanf(in, "%d", &aux.ID);
		getc(in);
		fscanf(in, "%c", &aux.type);
		getc(in);
		aux.availability = 1;
		add_nth_node(system->units, i, &aux);
		node *new_node = get_nth_element(system->units, i);
		void *location = new_node->data;
		enqueue(system->queue_available_units, location);
	}

	int commands = 0;
	fscanf(in, "%d", &commands);
	getc(in);
	for (int i = 0; i < commands; i++) {
		char *command = (char *)malloc(sizeof(char) * 200);
		if (!command) {
			free_system(&system);
			fprintf(stderr, "Allocation error for command");
			return 0;
		}
		fgets(command, 100, in);
		command[strlen(command) - 1] ='\0';
		command_processing(command, system);
		free(command);
	}

	free_system(&system);
	fclose(in);
}
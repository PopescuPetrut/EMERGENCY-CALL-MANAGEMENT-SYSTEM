#include "emergency_call.h"

int main(void)
{
	call_system *system = malloc(sizeof(call_system));
	if (!system) {
		fprintf(stderr, "System memory allocation faield");
		return -1;
	}
	system->queue_high = create_list(INCIDENT);
	system->queue_medium = create_list(INCIDENT);
	system->queue_low = create_list(INCIDENT);
	system->queue_units = create_list(UNITS);
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
		enqueue(system->queue_units, &aux);
	}

	int commands = 0;
	fscanf(in, "%d", &commands);
	getc(in);
	for (int i = 0; i < commands; i++) {
		char *command = (char *)malloc(sizeof(char) * 200);
		if (!command) {
			// free(system);
			fprintf(stderr, "Allocation error for command");
			return 0;
		}

		fgets(command, 100, in);
		command[strlen(command) - 1] ='\0';
		// command_processing(command, units);
		free(command);
	}	
}
#include "emergency_call.h"

int main(void)
{
	int nr_units;
	FILE *in = fopen("tema1.in", "rt");

	fscanf(in, "%d", &nr_units);
	getc(in);
	unit *units = (unit *)malloc(nr_units * sizeof(unit));
	if (!units) {
		fprintf(stderr, "Allocation error for units");
		return 0;
	}

	for (int i = 0; i < nr_units; i++) {
		fscanf(in, "%d", &units[i].ID);
		getc(in);
		fscanf(in, "%c", &units[i].type);
		getc(in);
		units[i].availability = 1;
	}

	int commands = 0;
	fscanf(in, "%d", &commands);
	getc(in);
	for (int i = 0; i < commands; i++) {
		char *command = (char *)malloc(sizeof(char) * 200);
		if (!command) {
			free(units);
			fprintf(stderr, "Allocation error for command");
			return 0;
		}

		fgets(command, 100, in);
		command[strlen(command) - 1] ='\0';
		// command_processing(command, units);
		free(command);
	}	
}
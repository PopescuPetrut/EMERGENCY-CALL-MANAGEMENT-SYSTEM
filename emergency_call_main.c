#include "emergency_call.h"

int main(void)
{
	int nr_units;
	FILE *in = fopen("tema1.in", "rt");

	fscanf(in, "%d", &nr_units);
	getc(in);
	unit *units = (unit *)malloc(nr_units * sizeof(unit));
	if (!units) {
		fprintf(stderr, "Allocation error");
		return 0;
	}

	for (int i = 0; i < nr_units; i++) {
		fscanf(in, "%d", &units[i].ID);
		getc(in);
		fscanf(in, "%c", &units[i].type);
		getc(in);
		units[i].availability = 1;
	}

	for (int i = 0; i < nr_units; i++) {
		printf("%d %c\n", units[i].ID, units[i].type);
	}
	
}
// POPESCU PETRUT - ALIN 312CA

#include "emergency_call.h"

void ADD_INCIDENT(char *command, call_system *system)
{
	incident new_incident;

	char *token = strchr(command, '"');
	new_incident.description = (char *)malloc(sizeof(char) * strlen(token) + 1);
	strcpy(new_incident.description, token);
	token = strtok(command, " ");
	token = strtok(NULL, " ");		
	new_incident.ID = atoi(token);
	token = strtok(NULL, " ");
	strcpy(new_incident.priority, token);
	strcpy(new_incident.status, "queued");

	add_nth_node(system->incidents, system->incidents->size, &new_incident);

	node *new_node = get_nth_element(system->incidents, system->incidents->size);
	void *location = new_node->data;
	if (!strcmp(new_incident.priority, "high")) {
		enqueue(system->queue_high, location);
	} else if (!strcmp(new_incident.priority, "medium")) {
		enqueue(system->queue_medium, location);
	} else if (!strcmp(new_incident.priority, "low")) {
		enqueue(system->queue_low, location);
	}

	free(new_incident.description);
}

void DISPATCH(call_system *system, FILE *file)
{
	node *curr_unit = NULL;
	node *curr_incident = NULL;

	if (!queue_isempty(system->queue_available_units)) {
		curr_unit = front(system->queue_available_units);
		((unit *)curr_unit->data)->availability = 0;
	}

	if (curr_unit) {
		if (!queue_isempty(system->queue_high)) {
			curr_incident = front(system->queue_high);
		} else if (queue_isempty(system->queue_high) && !queue_isempty(system->queue_medium)) {
			curr_incident = front(system->queue_medium);
		} else if (queue_isempty(system->queue_high) && queue_isempty(system->queue_medium) && !queue_isempty(system->queue_low)) {
			curr_incident = front(system->queue_low);
		}

		if (curr_incident) {
			strcpy(((incident *)curr_incident->data)->status, "intervened");

			intervention new_intervention;
			new_intervention.unit_to_deploy = curr_unit->data;
			new_intervention.incident_to_solve = curr_incident->data;
			
			add_nth_node(system->interventions, system->interventions->size, &new_intervention);
			
			node *aux = get_nth_element(system->interventions, system->interventions->size);
			intervention *data = (intervention *)aux->data;
			void *location = data;
			push(system->stack_interventions, location);
			dequeue(system->queue_available_units);
			if (!queue_isempty(system->queue_high)) {
				dequeue(system->queue_high);
			} else if (queue_isempty(system->queue_high) && !queue_isempty(system->queue_medium)) {
				dequeue(system->queue_medium);
			} else if (queue_isempty(system->queue_high) && queue_isempty(system->queue_medium) && !queue_isempty(system->queue_low)) {
				dequeue(system->queue_low);
			}
			
		} else {
			fprintf(file, "INVALID OPERATION! ERROR 404\n");
		}
	} else {
		fprintf(file, "INVALID OPERATION! ERROR 404\n");
	}
}

void UNDO_LAST_DISPATCH(call_system *system, FILE *file)
{
	if (stack_isempty(system->stack_interventions)) {
		fprintf(file, "INVALID OPERATION! ERROR 404\n");
		return;
	} else {
		int exist_problem = 0;

		while (!stack_isempty(system->stack_interventions)) {
			node *curr_intervention_ptr = top(system->stack_interventions);
			intervention *curr_intervention = (intervention *)curr_intervention_ptr->data;

			if (!strcmp(curr_intervention->incident_to_solve->status, "intervened")) {
				curr_intervention->unit_to_deploy->availability = 1;
				enqueue(system->queue_available_units, curr_intervention->unit_to_deploy);
				strcpy(curr_intervention->incident_to_solve->status, "queued");

				if (!strcmp(curr_intervention->incident_to_solve->priority, "high")) {
					priority_enqueue(system->queue_high, curr_intervention->incident_to_solve);
				} else if (!strcmp(curr_intervention->incident_to_solve->priority, "medium")) {
					priority_enqueue(system->queue_medium, curr_intervention->incident_to_solve);
				} else if (!strcmp(curr_intervention->incident_to_solve->priority, "low")) {
					priority_enqueue(system->queue_low, curr_intervention->incident_to_solve);
				}

				int find_pos = 0;
				for (int i = 0; i < system->interventions->size; i++) {
					node *it = get_nth_element(system->interventions, i);
					if (((intervention *)it->data)->incident_to_solve->ID == curr_intervention->incident_to_solve->ID) {
						find_pos = i;
						break;
					}
				}

				exist_problem = 1;
				remove_nth_node(system->interventions, find_pos);
				pop(system->stack_interventions);
				break;
			}
			pop(system->stack_interventions);
		}

		if (!exist_problem) {
			fprintf(file, "INVALID OPERATION! ERROR 404\n");
		} 
	}
}

void SOLVED_INCIDENT(char *command, call_system *system, FILE *file)
{
	strtok(command, " ");
	char *token = strtok(NULL, " ");
	int incident_id = atoi(token);

	if (system->interventions->size) {
		node *it = system->interventions->head->next;
		intervention *solved_intervention = (intervention *)it->data;
		incident *curr_incindent = solved_intervention->incident_to_solve;
		unit *curr_unit = solved_intervention->unit_to_deploy;

		for (int i = 0; i < system->interventions->size; i++) {
			if (curr_incindent->ID == incident_id && !strcmp(curr_incindent->status, "intervened")) {
				strcpy(curr_incindent->status, "solved");
				curr_unit->availability = 1;
				enqueue(system->queue_available_units, curr_unit);
				return;
			}
			if (it->next != system->interventions->head) {
				it = it->next;
				solved_intervention = (intervention *)it->data;
				curr_incindent = solved_intervention->incident_to_solve;
				curr_unit = solved_intervention->unit_to_deploy;
			} else {
				break;
			}
		}
	}
	fprintf(file, "INVALID OPERATION! ERROR 404\n");
}

void SHOW_UNIT(char *command, call_system *system, FILE *file)
{
	char *token = strtok(command, " ");
	token = strtok(NULL, " ");
	int unit_to_display = atoi(token);
	node *it = system->units->head->next;

	while (it != system->units->head) {
		if (((unit *)it->data)->ID == unit_to_display) {
			unit current_unit = *(unit *)it->data;

			if (current_unit.availability == 1) {
				fprintf(file, "Unit %d is type %c and is available\n", current_unit.ID, current_unit.type);
			} else {
				fprintf(file, "Unit %d is type %c and is unavailable\n", current_unit.ID, current_unit.type);
			}
			break;
		}
		it = it->next;
	}

	if (it == system->units->head) {
		fprintf(file, "INVALID OPERATION! ERROR 404\n");
	}
}

void SHOW_INCIDENT(char *command, call_system *system, FILE *file)
{
	char *token = strtok(command, " ");
	token = strtok(NULL, " ");
	int incident_to_displey = atoi(token);
	node *it = system->incidents->head->next;

	while (it != system->incidents->head) {
		if (((incident *)it->data)->ID == incident_to_displey) {
			incident current_incident = *(incident *)it->data;

			fprintf(file, "Incident %d has %s priority, the following description: %s and is %s\n", current_incident.ID, current_incident.priority, current_incident.description, current_incident.status);
			break;
		}
		it = it->next;
	}

	if (it == system->incidents->head) {
		fprintf(file, "INVALID OPERATION! ERROR 404\n");
	}
}

void SHOW_INTERVENTIONS(call_system *system, FILE *file)
{
	if (system->interventions->size) {
		for (int i = 0; i < system->interventions->size; i++) {
			node *it = get_nth_element(system->interventions, i);
			intervention *curr_inter = (intervention *)it->data;
			incident *curr_incident = (incident *)curr_inter->incident_to_solve;
			unit *curr_unit = (unit *)curr_inter->unit_to_deploy;

			fprintf(file, "Incident %d was assigned to unit %d, and has the following status: \"%s\"\n", curr_incident->ID, curr_unit->ID, curr_incident->status);
		}
	} else {
		fprintf(file, "No intervention has been initiated\n");
	}
}

// This function is processing the commands and calls the correct function to do the operation
void command_processing(char *command, call_system *system, FILE *output)
{
	if (!strncmp(command, "ADD_INCIDENT", 12)) {
		ADD_INCIDENT(command, system);

	} else if (!strcmp(command, "CHECK_UNITS_AVAILABILITY")) {
		fprintf(output, "Number of available units: %d\n", system->queue_available_units->size);

	} else if (!strcmp(command, "DISPATCH")) {
		DISPATCH(system, output);

	} else if (!strcmp(command, "UNDO_LAST_DISPATCH")) {
		UNDO_LAST_DISPATCH(system, output);

	} else if (!strncmp(command, "SOLVED_INCIDENT", 15)) {
		SOLVED_INCIDENT(command, system, output);

	} else if (!strncmp(command, "SHOW_UNIT", 9)) {
		SHOW_UNIT(command, system, output);

	} else if (!strncmp(command, "SHOW_INCIDENT", 13)) {
		SHOW_INCIDENT(command, system, output);

	} else if (!strcmp(command, "SHOW_INTERVENTIONS")) {
		SHOW_INTERVENTIONS(system, output);
	}
}
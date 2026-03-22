#include "emergency_call.h"

void command_processing(char *command, call_system *system)
{
	if (!strncmp(command, "ADD_INCIDENT", 12)) {
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
	} else if (!strcmp(command, "CHECK_UNITS_AVAILABILITY")) {
		printf("Number of available units: %d\n", system->queue_available_units->size);

	} else if (!strcmp(command, "DISPATCH")) {

	} else if (!strcmp(command, "UNDO_LAST_DISPATCH")) {

	} else if (!strncmp(command, "SOLVED_INCIDENT", 15)) {

	} else if (!strncmp(command, "SHOW_UNIT", 9)) {
		char *token = strtok(command, " ");
		token = strtok(NULL, " ");
		int unit_to_display = atoi(token);
		node *it = system->units->head->next;
		while(it != system->units->head) {
			if (((unit *)it->data)->ID == unit_to_display) {
				unit current_unit = *(unit *)it->data;
				if (current_unit.availability == 1) {
					printf("Unit %d is type %c and is available\n", current_unit.ID, current_unit.type);
				} else {
					printf("Unit %d is type %c and is unavailable\n", current_unit.ID, current_unit.type);
				}
				break;
			}
			it = it->next;
		}

		if (it == system->units->head) {
			printf("INVALID OPERATION! ERROR 404\n");
		}

	} else if (!strncmp(command, "SHOW_INCIDENT", 13)) {
		char *token = strtok(command, " ");
		token = strtok(NULL, " ");
		int incident_to_displey = atoi(token);
		node *it = system->incidents->head->next;
		while (it != system->incidents->head) {
			if (((incident *)it->data)->ID == incident_to_displey) {
				incident current_incident = *(incident *)it->data;
				printf("Incident %d has %s priority, the following description: %s and is %s\n", current_incident.ID, current_incident.priority, current_incident.description, current_incident.status);
				break;
			}
			it = it->next;
		}

		if (it == system->incidents->head) {
			printf("INVALID OPERATION! ERROR 404\n");
		}
	} else if (!strcmp(command, "SHOW_INTERVENTIONS")) {

	}
}
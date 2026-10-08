# EMERGENCY CALL MANAGEMENT SYSTEM

**Author**

* Popescu Petruţ - Alin

## INTRODUCTION

This project is a robust C-based simulation of an emergency response system. It manages the full lifecycle of incidents from initial reporting and priority queuing to unit dispatching and resolution using custom data structure implementations.

## DATA STRUCTURE

To manage units and emergencies, the system utilizes a **doubly circular linked list with a sentinel node**. To ensure efficient dispatching, the project uses a queue structure to prioritize emergencies. Incidents are split into three sets: **high priority**, **medium priority**, and **low priority**.

### Implementation Details
The implementation of the doubly circular linked list is generic. By using **void pointers**, the list can store any data type (structures, pointers, integers, etc.). When a list is initialized, an *enum* is used to specify the data type to facilitate proper memory handling.
* **Deep Copy:** Used when populating the primary lists for units, incidents, and interventions to ensure data persistence.
* **Shallow Copy:** Used for priority queues and the intervention stack, as these structures manage pointers to the existing data.


## PROGRAM FLOW

All system data is encapsulated in a structure called `call_system`, which contains pointers to eight different lists. These are categorized as follows:
* **Storage Lists:** Three lists that physically store the data for **Units**, **Incidents**, and **Interventions**.
* **Logic Lists:** Five lists of pointers used for management:
    * **Three Priority Queues:** To manage incidents based on their severity.
    * **Intervention Stack:** To manage a history of active interventions.
    * **Available Units Queue:** To track units ready for deployment.

The system begins by reading available units from a file and initializing the unit queue. Commands are handled through a central filter function, `command_process`, which interprets the input and executes the corresponding task.

---

### ADD INCIDENT 

**Parameters:** `ID`, `Priority`, `Description`  
This command adds an incident to the master list and places a pointer to that incident in the corresponding priority queue.

### DISPATCH 

**Parameters:** None  
Deploys an available unit to the highest-priority incident. If multiple incidents exist in the same priority tier, they are handled in the order they were added. Every active intervention is added to a **stack** to maintain a history.

### CHECK UNITS AVAILABLE

Prints the current number of units available in the system.

### UNDO LAST DISPATCH

Used to correct dispatching errors. It pops the most recent intervention from the stack, reverts the incident to the queue, and returns the unit to the available list.

### SOLVE INCIDENT

**Parameters:** `ID`  
Validates that a specific intervention is complete. The incident status is updated to "Solved," and the unit involved is re-added to the availability queue.

### SHOW UNIT AND SHOW INCIDENT

**Parameters:** `ID`  
Retrieves and prints all detailed information regarding a specific unit or incident by its unique identifier.

### SHOW INTERVENTIONS

Prints a comprehensive history of all interventions, including those currently in progress and those already solved.

> **[!WARNING]** > **IF ANY OF THE ABOVE FAILS IT RETURNS THE MESSAGE: "INVALID OPERATION! ERROR 404"**

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -g

TARGETS = emergency_call_main

build:$(TARGETS)

emergency_call_main: emergency_call_main.c command_processing.c functions_for_list_management.c functions_for_queue_management.c functions_for_stack_management.c
	$(CC) $(CFLAGS) emergency_call_main.c command_processing.c functions_for_list_management.c functions_for_queue_management.c functions_for_stack_management.c -o tema1

pack:
	zip -FSr Popescu_Petrut-Alin_312CA.zip *.c *.h Makefile README.md

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
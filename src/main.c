#include <stdio.h>

#include "task.h"

#define MULTIPLIER 2



void
task_a (void)
{
        for (int i = 0; i < 16 * MULTIPLIER; i++)
	{
		printf ("task_a\t: Hello! (Iter #%d)\n", i);
		task_yield();
	}

	task_terminate();
}



void
task_b (void)
{
	for (int i = 0; i < 8 * MULTIPLIER; i++)
	{
	        printf ("task_b\t: Hello! (Iter #%d)\n", i);
		task_yield();
	}

	task_terminate();
}



int
main (void)
{
	puts ("Starting tasking...");
	if (!task_setup())
	{
		fputs ("Failed to init tasking.\n", stderr);
		return -1;
	}

	if (!task_create (task_a))
	{
		fputs ("Failed to create task_a!\n", stderr);
	}

	if (!task_create (task_b))
	{
		fputs ("Failed to create task_b!\n", stderr);
	}

	puts ("Yielding to tasks...");
	for (int i = 0; i < 4 * MULTIPLIER; i++)
	{
	        printf ("main\t: Hello! (Iter #%d)\n", i);
		task_yield();
	}

	task_terminate();
}

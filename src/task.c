/******************************************************************************
 * Simple co-operative multitasking in C.                                     *
 *                                                                            *
 * Authors:                                                                   *
 *   Maxwell Powlison (bobdavelisafrank@protonmail.com)                       *
 *                                                                            *
 ******************************************************************************/
#include "task.h"

#include <stdio.h>
#include <stdlib.h>

/******************************************************************************
 * Function imports.                                                          *
 ******************************************************************************/

// Defined in task_asm.s.
extern          void task_switch (Task *old_t, Task *new_t);
extern noreturn void task_switch_destroy (Task *old_t, Task *new_t);

/******************************************************************************
 * Task queue -- for scheduling TIDs.                                         *
 ******************************************************************************/

static u16 task_queue[TASK_COUNT_MAX];
static u16 task_queue_count = 0;
static u16 task_queue_index = 0;

static void
task_queue_increment (void)
{
	if (task_queue_count != 0)
	{
		task_queue_index++;
		task_queue_index %= task_queue_count;
	}
}

static Task_ID
task_queue_current (void)
{
	return task_queue[task_queue_index];
}

static Task_ID
task_queue_next (void)
{
	task_queue_increment();
	return task_queue_current();
}

static void
task_queue_add (Task_ID tid)
{
	task_queue[task_queue_count] = tid;
	task_queue_count++;
}

static void
task_queue_make_current (Task_ID tid)
{
	task_queue_index = tid;
}

static void
task_queue_remove_current (void)
{
	if (task_queue_count <= task_queue_index)
	{
		fputs ("Task queue index out of range!", stderr);
	        abort();
	}
	else if (task_queue_index == task_queue_count - 1)
	{
		task_queue_count--;
	}
	else
	{
		task_queue_count--;
		task_queue[task_queue_index] = task_queue[task_queue_count];
	}
}

/******************************************************************************
 * Task table, for associating TIDs with data.                                *
 ******************************************************************************/

// Task table - Associate TID with task data.
static Task *task_table [TASK_COUNT_MAX];

static Task *
task_table_lookup (Task_ID tid)
{
	return task_table[tid];
}

static Task *
task_table_new (void)
{
	Task_ID tid = 0;

	for (; tid < TASK_COUNT_MAX; tid++)
		if (task_table[tid] == NULL)
			break;

	if (tid == TASK_COUNT_MAX)
		return NULL;

	task_table[tid] = malloc (sizeof (Task));

	if (task_table[tid] == NULL)
		return NULL;
	
	task_table[tid] -> id = tid;

	return task_table[tid];
}

static void
task_table_delete (Task_ID tid)
{
	free (task_table[tid]);
	task_table[tid] = NULL;
}

/******************************************************************************
 * Handling of task data-structures.                                          *
 ******************************************************************************/

Task *
task_raw_create (void (*start)(void))
{
	Task *t = task_table_new();

	if (t == NULL)
		return NULL;

	t -> start_addr = (u64) start;

	if (start != NULL)
	{
		t -> load_count   = 0;
		t -> stack_start  = (u64) (malloc (TASK_STACK_SIZE));
		t -> stack_start += TASK_STACK_SIZE; // Stacks grow downwards.
	}
	else
	{
		// For initializer thread, which has already been loaded and
		// has a stack.
		t -> load_count = 1;
		t -> stack_start = 0;
	}

	return t;
}

void
task_raw_destroy (Task *t)
{
	if (t == NULL)
		return;

	if (t -> stack_start != 0)
	{
		u64 stack_base = t -> stack_start - TASK_STACK_SIZE;
		
		free ((void *) stack_base);
	}
	
	task_table_delete (t -> id);
}

/******************************************************************************
 * Tasking interface.                                                         *
 ******************************************************************************/

bool
task_create (void (*start)(void))
{
	Task *t = task_raw_create (start);

	if (t == NULL)
		return false;

	task_queue_add (t -> id);

	return true;
}

noreturn void
task_terminate (void)
{
	Task_ID cur_tid = task_queue_current();
	task_queue_remove_current();
	
	Task_ID new_tid = task_queue_next();

	if (cur_tid != new_tid)
	{
		Task *cur_t = task_table_lookup (cur_tid);
		Task *new_t = task_table_lookup (new_tid);

	        task_switch_destroy (cur_t, new_t);
	}
	else
	{
	        exit (0);
	}
}

void
task_yield (void)
{
	Task_ID cur_tid = task_queue_current();
	Task_ID new_tid = task_queue_next();

	if (cur_tid != new_tid)
	{
		Task *cur_t = task_table_lookup (cur_tid);
		Task *new_t = task_table_lookup (new_tid);
        
		task_switch (cur_t, new_t);
	}
}

bool
task_setup (void)
{
        Task *t = task_raw_create (NULL);

	if (t == NULL)
		return false;

	task_queue_add (t -> id);
	task_queue_make_current (t -> id);

	return true;
}

/* ----------------------------------- EOF ---------------------------------- */

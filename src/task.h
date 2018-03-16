/******************************************************************************
 * Simple co-operative multitasking in C.                                     *
 *                                                                            *
 * Authors:                                                                   *
 *   Maxwell Powlison (bobdavelisafrank@protonmail.com)                       *
 *                                                                            *
 ******************************************************************************/
#pragma once

#include <std/int.h>

/******************************************************************************
 * Configuration.                                                             *
 ******************************************************************************/

#ifndef   TASK_COUNT_MAX
#  define TASK_COUNT_MAX 64
#endif

#ifndef   TASK_STACK_SIZE
#  define TASK_STACK_SIZE 16384
#endif

/******************************************************************************
 * Tasking structures.                                                        *
 ******************************************************************************/

typedef u16 Task_ID;

typedef struct
{
	u64 rbx; // + 0x00
	u64 rsp; // + 0x08
	u64 rbp; // + 0x10
	u64 r12; // + 0x18
	u64 r13; // + 0x20
	u64 r14; // + 0x28
	u64 r15; // + 0x30
}
PACKED Task_Registers;

typedef struct
{
	Task_Registers reg; // + 0x00
	u64 start_addr;     // + 0x38
	u64 load_count;     // + 0x40
	u64 stack_start;    // + 0x48
	
	Task_ID id;
}
PACKED Task;

/******************************************************************************
 * Handling of task data-structures.                                          *
 ******************************************************************************/

Task *
task_raw_create (void (*start)(void));

void
task_raw_destroy (Task *t);

/******************************************************************************
 * Tasking interface.                                                         *
 ******************************************************************************/

bool
task_create (void (*start)(void));

noreturn void
task_terminate (void);

void
task_yield (void);

bool
task_setup (void);

/* ----------------------------------- EOF ---------------------------------- */

;;----------------------------------------------------------------------------;;
;; Simple co-operative multitasking.                                          ;;
;;                                                                            ;;
;; Authors:                                                                   ;;
;;   Maxwell Powlison (bobdavelisafrank@protonmail.com)                       ;;
;;----------------------------------------------------------------------------;;

SECTION	.text
	
extern	task_raw_destroy
extern	task_terminate
	
;; SYSV AMD64 calling conventions:
;;
;; Saved registers:
;;   rbx
;;   rsp
;;   rbp
;;   r12
;;   r13
;;   r14
;;   r15
;;   
;; Stack:
;;   (optional) 8 bytes -- frame pointer (RBP)
;;   Return RIP
;;
;; GCC options:
;;   -fomit-frame-pointer :
;;     Guarantees that the frame-pointer is not present.
;;

;; Structures: 
;;
;; Task_Registers:
;;   rbx // + 0x00
;;   rsp // + 0x08
;;   rbp // + 0x10
;;   r12 // + 0x18
;;   r13 // + 0x20
;;   r14 // + 0x28
;;   r15 // + 0x30
;;
;; Task:
;;   Task_Registers reg // + 0x00
;;   u64 start_addr     // + 0x38
;;   u64 load_count     // + 0x40
;;   u64 stack_start    // + 0x48
;;   (...)
;;

;; void task_switch (Task *cur_t, Task *new_t)
global	task_switch
task_switch:
	;; Save old task.
	mov	[rdi + 0x00],	rbx
	mov	[rdi + 0x08],	rsp
	mov	[rdi + 0x10],	rbp
	mov	[rdi + 0x18],	r12
	mov	[rdi + 0x20],	r13
	mov	[rdi + 0x28],	r14
	mov	[rdi + 0x30],	r15

	jmp	task_load

;; void task_switch_destroy (Task *cur_t, Task *new_t)
global	task_switch_destroy
task_switch_destroy:
	mov	rsp,	task_destroy_stack
	
	push	rsi
	sub	rsp,	8
	push	rbp
	mov	rbp,	rsp
	call	task_raw_destroy
	mov	rsp,	rbp
	pop	rbp
	add	rsp,	8
	pop	rsi

	jmp	task_load

;; task_load (RSI Task *);
task_load:
	;; Check for first load.
	mov	rax,	[rsi + 0x40] ; (Task *) -> load_count
	cmp	rax,	0
	je	.first_load
	inc	rax
	mov	[rsi + 0x40],	rax
	
	mov	rbx,	[rsi + 0x00] ; (Task *) -> reg
	mov	rsp,	[rsi + 0x08]
	mov	rbp,	[rsi + 0x10]
	mov	r12,	[rsi + 0x18]
	mov	r13,	[rsi + 0x20]
	mov	r14,	[rsi + 0x28]
	mov	r15,	[rsi + 0x30]

	cld
	ret

.first_load:
	mov	rax,	[rsi + 0x38] 	  ; RIP: (Task *) -> start_addr
	mov	qword [rsi + 0x40],	1 ; Increment load count.
	mov	rsp,	[rsi + 0x48]	  ; RSP: (Task *) -> stack_start

	; Set up this function's stack-frame (since new RSP is in place).
	mov	rbp,	rsp

	; Peform the load.
	push	rbp
	mov	rbp,	rsp
	call	rax
	mov	rsp,	rbp

	; In case of return.
	call	task_terminate

SECTION	.bss
	resq	128
	task_destroy_stack	equ	$

;;----------------------------------------------------------------------------;;

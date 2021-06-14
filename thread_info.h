...
/*
 * low level task data that entry.S needs immediate access to
 * - this struct should fit entirely inside of one cache line
 * - if the members of this struct changes, the assembly constants
 *   in asm-offsets.c must be updated accordingly
 * - thread_info is included in task_struct at an offset of 0.  
 *   This means that tp points to both thread_info and task_struct.
 */
struct thread_info {
	/* low level flags */
	unsigned long		flags;	
	/* 0=>preemptible, <0=>BUG */
	int                     preempt_count;  
	/*
	 * These stack pointers are overwritten on every system 
	 * call or exception.  SP is also saved to the stack 
	 * it can be recovered when overwritten.
	 */
	/* Kernel stack pointer */
	long			kernel_sp;	
	/* User stack pointer */
	long			user_sp;	
	int			cpu;
};
...



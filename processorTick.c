#include <time.h>
#include <sched.h>
#include <stdio.h>
#include <unistd.h>
int counter=0;

void processorTick() __attribute__ (( naked ));
void SIG_OUTPUT_COMPARE1A( void ) __attribute__ (( signal, naked));
void processorTick()
{
	/* This is a naked function so the context is saved. */
    	
	//portSAVE_CONTEXT();

	/* Increment the tick count and check to see if the new tick value has caused a delay period to expire.  This function call can cause a task to become ready to run. */
	//vTaskIncrementTick();
	counter++;


	/* See if a context switch is required. Switch to the context of a task made ready to run by vTaskIncrementTick() if it has a priority higher than the interrupted task. */

	//vTaskSwitchContext();

	/* Restore the context.  If a context switch has occurred this will restore the context of the task being resumed. */
	
	//portRESTORE_CONTEXT();

	/* Return from this naked function. */
	printf("processorTick\n");
	asm volatile ( "ret" );
}


void SIG_OUTPUT_COMPARE1A( void )
{

	printf("start\n");
	processorTick();
	
	asm volatile ( "ret" );
}

int main()
{
	SIG_OUTPUT_COMPARE1A();
	return 0;
}
 








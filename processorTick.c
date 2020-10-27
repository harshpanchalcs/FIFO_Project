#include <time.h>
#include <stdio.h>
#include <unistd.h>
int counter=0;

void SIG_OUTPUT_COMPARE1A( void ) __attribute__ (( signal, naked ));
void processorTick()
{
	counter++;
	/*if(some process will unblock)
	{
	}*/
	printf("processorTick\n");
	return;
}


void SIG_OUTPUT_COMPARE1A( void )
{
    /* ISR C code for RTOS tick. */
	portSAVE_CONTEXT();
	
	printf("start\n");
	processorTick();
	
	portRESTORE_CONTEXT();

	asm volatile ( "ret" );
	
	
}

int main()
{
	SIG_OUTPUT_COMPARE1A();
	return 0;
}
 








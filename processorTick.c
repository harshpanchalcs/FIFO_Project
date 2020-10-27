#include <time.h>
#include <stdio.h>
#include <unistd.h>
int counter=0;


void processorTick()
{
	counter++;
	/*if(some process will unblock)
	{
	}*/
	printf("processorTick\n");
	return;
}


void SIG_OUTPUT_COMPARE( void ) __attribute__ ( ( signal ) )
{
    /* ISR C code for RTOS tick. */
    processorTick();
    printf("start");
}

int main()
{
	SIG_OUTPUT_COMPARE();
	return 0;
}
 








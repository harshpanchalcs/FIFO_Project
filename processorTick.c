#include <time.h>
#include <stdio.h>
#include <unistd.h>
int counter=0;

void processorTick() __attribute__ (( naked ));
void SIG_OUTPUT_COMPARE1A( void ) __attribute__ (( signal, naked));
void processorTick()
{
	//portSAVE_CONTEXT();	
	
	counter++;

	//portRESTORE_CONTEXT();
	/*if(some process will unblock)
	{
	}*/
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
 








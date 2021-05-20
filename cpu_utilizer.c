#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define no_threads 10

void *one(void *arg)
{

	 // Start measuring time
	    struct timespec begin, end; 
	    clock_gettime(CLOCK_REALTIME, &begin);
    
	long int x=10000000,y;
	while(x--)
	{
		y = 1000;
		while(y--)
		{
		
		}
	}
	
	// Stop measuring time and calculate the elapsed time
	    clock_gettime(CLOCK_REALTIME, &end);
	    long seconds = end.tv_sec - begin.tv_sec;
	    long nanoseconds = end.tv_nsec - begin.tv_nsec;
	    double elapsed = seconds + nanoseconds*1e-9;
    
   	printf("Time measured for thread %d is: %f seconds.\n", *((int*)arg), elapsed);
}



int main () {


	pthread_t thread_id[no_threads];
	int count[no_threads];
	
	// Start measuring time
	    struct timespec begin, end; 
	    clock_gettime(CLOCK_REALTIME, &begin);
	
	for(int i=0; i<no_threads; i++)
	{
		count[i]=i;
		pthread_create(&thread_id[i], NULL, one, (void*)(&count[i]));
	}
	
	for(int i=0; i<no_threads; i++)
	{
		pthread_join(thread_id[i], NULL);
	}    
	
	// Stop measuring time and calculate the elapsed time
	    clock_gettime(CLOCK_REALTIME, &end);
	    long seconds = end.tv_sec - begin.tv_sec;
	    long nanoseconds = end.tv_nsec - begin.tv_nsec;
	    double elapsed = seconds + nanoseconds*1e-9;
    
   	printf("Time measured: %f seconds.\n", elapsed);
    
    return 0;
}

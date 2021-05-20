#include<stdio.h>
#include <stdlib.h>
#include <sched.h>
#include<time.h>
#include <math.h>

#define times 20
#define processes 1000 // always greater then 2

void sorting(int *arr)
{
	int temp, j;
	for(int i=1; i<processes; i++)
	{
		temp = arr[i];
		j = i-1;
		while(j>=0 && arr[j] > temp)
		{
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = temp;
	}
}


void main()
{
	int arr[processes];
	double record[times]={0}, elapsed, mean=0, variance=0;
	struct timespec begin, end;
	
	for(int j=0; j<times; j++)
	{
		srand(time(0));
		for(int i=0; i<processes; i++)
		{
			arr[i] = rand()%processes;
		}
			
		clock_gettime(CLOCK_REALTIME, &begin);	
		sorting(arr);
		clock_gettime(CLOCK_REALTIME, &end);
		record[j] = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec)*1e-9;
	}
	for(int j=0; j<times; j++)
	{
		printf("%2d -> %f\n", j+1, record[j]);
		mean += record[j];
	}
	mean /= (double)times;
	for(int j=0; j<times; j++)
	{
		variance += (record[j] - mean)*(record[j] - mean);
	}
	variance /= (double)times;
	
	printf("\n\n mean = %f \n variance = %f\n", mean*1000, variance*1000); 
	
}


	
	/*for(int i=0; i<processes; i++)
	{
		printf("%d ", arr[i]);
	}	*/
	
	/*printf("\n");
	for(int i=0; i<processes; i++)
	{
		printf("%d ", arr[i]);
	}*/

/*	struct sched_param param;
	int pid_num = 0;

	param.sched_priority = 99;
	sched_setscheduler(pid_num, SCHED_FIFO, &param);
	while (1); 
*/

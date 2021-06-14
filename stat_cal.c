#include<stdio.h>
#include <stdlib.h>
#include <sched.h>
#include<time.h>
#include <math.h>
#include <pthread.h>

#define no_threads 2  // Do not change
#define processes 5000 // always greater then 2
#define times 100


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


void *half_sort(void *arg)
{
	int temp, j;
	int *arr = (int*)arg;
	for(int i=1; i<processes/no_threads; i++)
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

void sorting_thread(int *arr)
{
	pthread_t thread_id[no_threads];
	for(int i=0; i<no_threads; i++)
	{
		pthread_create(&thread_id[i], NULL, half_sort, (void*)(&arr[i*(processes/no_threads)]));
	}
	
	for(int i=0; i<no_threads; i++)
	{
		pthread_join(thread_id[i], NULL);
	} 
	
	// for merging two halfs of the array;
	int t_arr[processes];
	for(int i=0; i<processes; i++)
	{
		t_arr[i] = arr[i];
	}
	int i=0, j=processes/no_threads, k=0;
	while(i<processes/no_threads && j<processes)
	{
		arr[k++] = (t_arr[i]<=t_arr[j])?t_arr[i++]:t_arr[j++];
	}
	while(i<processes/no_threads)
	{
		arr[k++]=t_arr[i++];
	}
	while(j<processes)	
	{
		arr[k++]=t_arr[j++];
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
		//sorting_thread(arr);
		
		clock_gettime(CLOCK_REALTIME, &end);
		record[j] = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec)*1e-9;
		
		printf("\n%2d -> %f", j+1, record[j]);
		mean += record[j];
		
	}
	
	mean /= (double)times;
	for(int j=0; j<times; j++)
	{
		variance += (record[j] - mean)*(record[j] - mean);
	}
	variance /= (double)times;
	
	variance = sqrt(variance);
	
	printf("\n\n mean = %f \n standard deviation = %f\n", mean*1000, variance*1000); 
	
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

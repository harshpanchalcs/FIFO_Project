#include<stdio.h>
#include <stdlib.h>
#include <sched.h>
#include<time.h>
#include <math.h>
#include <pthread.h>

#define processes 10000 // always greater then 2
#define times 20

struct task_struct
{
	int PID;
	int prio;
};
struct rq
{
	struct task_struct *task;
	struct rq *next, *prev;
};

struct task_struct* pick_next_task(struct rq *rq, struct task_struct *prev);
struct rq* add_rq(struct rq *rq);
void free_rq(struct rq *rq);

void print_rq(struct rq *rq);

void main()
{
	double record[times]={0}, elapsed, mean=0, variance=0;
	struct timespec begin, end;
	srand(time(0));
	
	for(int j=0; j<times; j++)
	{
	
		struct rq *head=NULL;
		head = add_rq(head);
		clock_gettime(CLOCK_REALTIME, &begin);
		
		struct task_struct *next = pick_next_task(head, NULL);
		
		clock_gettime(CLOCK_REALTIME, &end);
		record[j] = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec)*1e-9;
		
		printf("\n%2d -> %f", j+1, record[j]*1000);
		mean += record[j];
		
		printf("   %d %d", next->PID, next->prio);
		//print_rq(head);
		
		free_rq(head);
		
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


struct task_struct* pick_next_task(struct rq *rq, struct task_struct *prev)
{
	struct task_struct *max = rq->task;
	struct rq *temp = rq->next;
	while(temp!=rq)
	{
		if(temp->task->prio > max->prio)
		{
			max = temp->task;
		}
		temp = temp->next;
	}
	return max;
}


struct rq* add_rq(struct rq *rq)
{
	
	for(int i=0; i<processes; i++)
	{
		struct task_struct *temp = (struct task_struct*)malloc(sizeof(struct task_struct));
		temp->PID = i;
		temp->prio = rand()%processes;
		struct rq *addition = (struct rq*)malloc(sizeof(struct rq));
		addition->task = temp;
		addition->next = NULL;
		addition->prev = NULL;
	
		if(rq==NULL)
		{
			rq = addition;
			rq->next = rq;
			rq->prev = rq;
		}
		else
		{
			addition->next = rq;
			addition->prev = rq->prev;
			if(rq->prev != NULL)
			{
				rq->prev->next = addition;
				rq->prev = addition;
			}
		}
		//printf("(%d-%d)",rq->prev->task->PID, rq->prev->task->prio);
	}
	return rq;
}

void free_rq(struct rq *rq)
{
	struct rq *temp;
	while(rq != NULL)
	{
		temp = rq;
		rq = rq->next;
		if(temp->prev != NULL)
		{
			temp->prev->next = NULL;
		}
		if(temp->next != NULL)
		{
			temp->next->prev = NULL;
		}
		//printf("      %d  %d\n", temp->task->PID, temp->task->prio);
		free(temp->task);
		free(temp);
	}
}

void print_rq(struct rq *rq)
{
	printf(" %d-%d",rq->task->PID,rq->task->prio);
	struct rq *temp = rq->next;
	while(temp!=rq)
	{
		printf(" %d-%d",temp->task->PID,temp->task->prio);
		temp = temp->next;
	}
}


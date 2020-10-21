#include <stdio.h>
#include <stdlib.h>

struct process  //structure that stores the information about process
{
	int pid;
	int arrival_time;
};

struct process* create_process()    //function for taking inputs for the information of process
{ 
	struct process *p = (struct process*)malloc(sizeof(struct process));
	printf("Enter Process Id : \n");
	scanf("%d", &(p->pid) );
	return p;
}


struct queue       //queue for the FIFO scheduler to maintain a sequence of processes
{
	struct process *p;
	struct queue *next;
};

struct queue* create_queue(struct process *p)  //function that makes a queue node
{
	struct queue *q = (struct queue*)malloc(sizeof(struct queue));
	q->p = p;
	q->next = NULL;
	return q;
}


void insert_process(struct queue **start, struct queue **end)   //function for inserting a process into FIFO scheduler queue
{
	struct process *p = create_process();
	struct queue *q = create_queue(p);
	if(*end == NULL)
	{
		*start = q;
		*end = q;
	}
	else
	{
		(*end)->next = q;
		*end = q;
	}
}

struct process* schedule_process(struct queue **start, struct queue **end) //function returns a process which will schedule
{
	if(*start == NULL)
	{
		return NULL;
	}
	struct process *p;
	struct queue *q;
	q = *start;
	if(*start == *end)
	{
		
		*start = NULL;
		*end = NULL;
	}
	else
	{
		*start = (*start)->next;
	}
	p = q->p;
	free(q);
	return p;
}

int main()
{
	
	struct queue *start=NULL, *end=NULL;
	struct process *p;
	int x = 1;
	while(x)
	{
		printf("Enter 1 for Insert Process & 2 for Schedule Process :\n");
		scanf("%d", &x);
		if(x == 1)
		{
			insert_process(&start, &end);         //it calls when new process created and process is ready for execution
		}
		else if(x == 2)
		{	
			p = schedule_process(&start, &end);   //it calls when resources are free and want to schedule ready process
			if(p==NULL)
			{
				printf("There is no process for schedule...\n");
			}
			else
			{			
				printf("pid = %d is scheduled...\n", p->pid);
				free(p);
			}
		}
		printf("\n");
	}
	printf("Run\n");
	return 0;
}


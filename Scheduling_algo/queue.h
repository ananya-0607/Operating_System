#include<stdio.h>
# define queue_size 100

struct queue
{
    int list_process[100];
    int front;
    int rear;
};

void inizialisation(struct queue *q);
int is_empty(struct queue *q);
int is_full(struct queue *q);
int enqueue(struct queue *q,int process_id);
int dequeue(struct queue *q);
int is_in(struct queue *q,int process_id);

void inizialisation(struct queue *q)
{
    q->front=-1;
    q->rear=-1;
}

int is_empty(struct queue *q)
{
    if(q->front==-1)
    {
        printf("Queue is Empty.\n");
        return 1;
    }
    return 0;
}

int is_full(struct queue *q)
{
    if(q->rear==queue_size-1)
    {
        printf("Queue is full.\n");
        return 1;
    }
    return 0;
}

int enqueue(struct queue *q,int process_id)
{
    if(q->rear==queue_size-1)
    {
        printf("Queue is full.\n");
        return 0;
    }
    if(q->front==-1)
    {
        q->front=0;
    }
    q->rear++;
    q->list_process[q->rear]=process_id;
    return 1;
}

int dequeue(struct queue *q)
{
    if(q->front==-1)
    {
        printf("Queue is Empty.\n");
        return 0;
    }
    int x=q->list_process[q->front];
    q->front++;
    if(q->front>q->rear)
    {
        q->front=-1;
        q->rear=-1;
    }
    return x;
}

int is_in(struct queue *q , int process_id)
{
    if(q->front==-1)
    {
        return 0;
    }
    for(int i=q->front;i<q->rear;i++)
    {
        if(q->list_process[i]==process_id)
        {
            return 1;
        }
    }
    return 0;
}

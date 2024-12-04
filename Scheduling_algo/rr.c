#include<stdio.h>
#include<stdlib.h>
#include "queue.h"

typedef struct 
{
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
    int remaining_time;
    int completion_time;
}Process;

void rr_proc(Process process[],int n,int quantum)
{
    int time=0;
    int complete=0;
    double total_waiting_time=0;
    double total_turnaround_time=0;
    double total_response_time=0;

    for(int i=0;i<n;i++)
    {
        process[i].remaining_time=process[i].burst_time;
        process[i].response_time=-1;
    }

    struct queue q;
    inizialisation(&q);

    for(int i=0;i<n;i++)
    {
        if(process[i].arrival_time==0)
        {
            enqueue(&q,i);
        }
    }

    while(complete!=n)
    {
        int item=dequeue(&q);

        if(process[item].response_time==-1)
        {
            process[item].response_time=time-process[item].arrival_time;
            total_response_time+=process[item].response_time;
        }

        int execute_time=(process[item].remaining_time>quantum) ? quantum : process[item].remaining_time;
        time+=execute_time;
        process[item].remaining_time-=execute_time;

        for(int i=0;i<n;i++)
        {
            if(process[i].arrival_time>time-execute_time && process[i].arrival_time<=time && process[i].remaining_time>0 && is_in(&q,i)==0)
            {
                enqueue(&q,i);
            }
        }

        if(process[item].remaining_time>0)
        {
            enqueue(&q,item);
        }
        else
        {
            complete++;
            process[item].completion_time=time;
            process[item].turnaround_time=process[item].completion_time-process[item].arrival_time;
            process[item].waiting_time=process[item].turnaround_time-process[item].burst_time;
            total_turnaround_time+=process[item].turnaround_time;
            total_waiting_time+=process[item].waiting_time;
        }

    }

    printf("PROCESS ID\tARRIVAL TIME\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\tRESPONSE TIME\n");
    for(int i=0;i<n;i++)
    {
        printf("P%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n",
        process[i].process_id,
        process[i].arrival_time,
        process[i].burst_time,
        process[i].waiting_time,
        process[i].turnaround_time,
        process[i].response_time);
    }
    printf("Average waiting time : %f\n",total_waiting_time/n);
    printf("Average turn around time : %f\n",total_turnaround_time/n);
    printf("Average response time : %f\n",total_response_time/n);
}

int main()
{
    int n;
    int quantum;
    printf("Enter the number of processes : ");
    scanf("%d",&n);
    Process process[n];
    for(int i=0;i<n;i++)
    {
        process[i].process_id=i+1;
        printf("Enter the access time of p%d : ",i+1);
        scanf("%d",&process[i].arrival_time);
        printf("Enter the burst time of p%d : ",i+1);
        scanf("%d",&process[i].burst_time);
    }
    printf("Enter the time quantum : ");
    scanf("%d",&quantum);

    rr_proc(process,n,quantum);

    return 0;
}

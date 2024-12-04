#include<stdio.h>
#include<stdbool.h>
#include<limits.h>

typedef struct 
{
    int process_id;
    int priority;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int response_time;
    int turnaround_time;
    int completion_time;
    bool completed;
}Process;

void pnp_proc(Process process[],int n)
{
    int time=0;
    int complete=0;
    double total_waiting_time=0;
    double total_turnaround_time=0;
    double total_response_time=0;

    for(int i=0;i<n;i++)
    {
        process[i].completed=false;
    }

    while(complete!=n)
    {
        int max_val=INT_MIN;
        int high_priority=-1;

        for(int i=0;i<n;i++)
        {
            if(process[i].arrival_time<=time && process[i].completed==false && process[i].priority>max_val)
            {
                max_val=process[i].priority;
                high_priority=i;
            }
        }

        if(high_priority==-1)
        {
            time++;
            continue;
        }

        process[high_priority].completion_time=time+process[high_priority].burst_time;
        process[high_priority].turnaround_time=process[high_priority].completion_time-process[high_priority].arrival_time;
        process[high_priority].waiting_time=process[high_priority].turnaround_time-process[high_priority].burst_time;
        process[high_priority].response_time=process[high_priority].waiting_time;

        time+=process[high_priority].burst_time;
        process[high_priority].completed=true;
        complete++;

        total_response_time+=process[high_priority].response_time;
        total_turnaround_time+=process[high_priority].turnaround_time;
        total_waiting_time+=process[high_priority].waiting_time;

    }

    printf("PROCESS ID\tARRIVAL TIME\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\t\tRESPONSE TIME\n");
    for(int i=0;i<n;i++)
    {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n",
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
        printf("Enter the priority of p%d : ",i+1);
        scanf("%d",&process[i].priority);
    }
    pnp_proc(process,n);
    return 0;
}
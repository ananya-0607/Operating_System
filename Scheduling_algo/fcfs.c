#include<stdio.h>

typedef struct 
{
    int process_id;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int waiting_time;
    int response_time;
    int turnaround_time;
}Process;

void fcfs_proc(Process process[],int n)
{
    int time=0;
    double total_waiting_time=0;
    double total_turnaround_time=0;
    double total_response_time=0;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(process[j].arrival_time>=process[j+1].arrival_time)
            {
                Process temp=process[j];
                process[j]=process[j+1];
                process[j+1]=temp;
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        if(time<process[i].arrival_time)
        {
            time=process[i].arrival_time;
        }

        process[i].start_time=time;
        process[i].completion_time=time+process[i].burst_time;
        process[i].turnaround_time=process[i].completion_time-process[i].arrival_time;
        process[i].waiting_time=process[i].turnaround_time-process[i].burst_time;
        process[i].response_time=process[i].waiting_time;

        total_response_time+=process[i].response_time;
        total_turnaround_time+=process[i].turnaround_time;
        total_waiting_time+=process[i].waiting_time;

        time+=process[i].burst_time;

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

    fcfs_proc(process,n);

    return 0;
}
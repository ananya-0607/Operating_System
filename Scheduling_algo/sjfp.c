#include<stdio.h>
#include<stdbool.h>
#include<limits.h>

typedef struct 
{
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
    int remaining_time;
    bool started;
    bool completed;
}Process;

void sjfp_proc(Process process[],int n)
{
    int time=0;
    int complete=0;
    double total_waiting_time=0;
    double total_turnaround_time=0;
    double total_response_time=0;

    for(int i=0;i<n;i++)
    {
        process[i].remaining_time=process[i].burst_time;
        process[i].started=false;
        process[i].completed=false;
    }

    while(complete!=n)
    {
        int shortest=-1;
        int min_val=INT_MAX;

        for(int i=0;i<n;i++)
        {
            if(process[i].arrival_time<=time && process[i].completed==false && process[i].remaining_time<min_val)
            {
                min_val=process[i].remaining_time;
                shortest=i;
            }
        }

        if(shortest==-1)
        {
            time++;
            continue;
        }

        if(process[shortest].started==false)
        {
            process[shortest].response_time=time-process[shortest].arrival_time;
            total_response_time+=process[shortest].response_time;
            process[shortest].started=true;
        }

        process[shortest].remaining_time--;
        time++;

        if(process[shortest].remaining_time==0)
        {
            process[shortest].completed=true;
            process[shortest].turnaround_time=time-process[shortest].arrival_time;
            process[shortest].waiting_time=process[shortest].turnaround_time-process[shortest].burst_time;
            total_turnaround_time+=process[shortest].turnaround_time;
            total_waiting_time+=process[shortest].waiting_time;
            complete++;
        }
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
    }
    sjfp_proc(process,n);
    return 0;
}
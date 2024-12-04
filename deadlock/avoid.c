#include<stdio.h>
#include<stdbool.h>

#define num_process 5
#define num_resources 3

int allocation[num_process][num_resources],max[num_process][num_resources],need[num_process][num_resources];
int available[num_resources];
int work[num_resources];

void calculateneed()
{
    for(int i=0;i<num_process;i++)
    {
        for(int j=0;j<num_resources;j++)
        {
            need[i][j]=max[i][j]-allocation[i][j];
        }
    }
}

bool issafe()
{
    bool finish[num_process]={false};

    for(int i=0;i<num_process;i++)
    {
        work[i]=available[i];
    }

    int count=0;
    while(count!=num_process)
    {
        bool found=false;
        for(int i=0;i<num_process;i++)
        {
            int j;
            if(finish[i]==false)
            {
                for(j=0;j<num_resources;j++)
                {
                    if(need[i][j]>work[j])
                    {
                        break;
                    }
                }

                if(j==num_resources)
                {
                    for(int k=0;k<num_resources;k++)
                    {
                        work[k]+=allocation[i][k];
                        finish[i]=true;
                        count++;
                        found=true;
                    }
                }
            }
        }
        if(found==false)
        {
            printf("Unsafe state");
            return false;
        }
    }
    printf("Safe mode");
    return true;
}


int requestresource(int process_id,int request[])
{
    for(int i=0;i<num_resources;i++)
    {
        if(request[i]>need[process_id][i])
        {
            printf("The process is asking more than what it need\n");
            return -1;
        }
    }
    for(int i=0;i<num_resources;i++)
    {
        if(request[i]>available[i])
        {
            printf("The process is asking more that what is available\n");
            return -1;
        }
    }
    for(int i=0;i<num_resources;i++)
    {
        available[i]-=request[i];
        allocation[process_id][i]+=request[i];
        need[process_id][i]-=request[i];
    }
    if(issafe()==false)
    {
        for(int i=0;i<num_resources;i++)
        {
            available[i]+=request[i];
            allocation[process_id][i]-=request[i];
            need[process_id][i]+=request[i];
        }
        printf("Resources cannot be allocated to process %d as it leads to unsafe state.\n", process_id + 1);
        return -1;
    }
    else
    {
        printf("Resources allocated successfully to process %d.\n", process_id + 1);
        return 0;
    }
}

int main()
{
    for(int i=0;i<num_process;i++)
    {
        for(int j=0;j<num_resources;j++)
        {
            printf("Enter the allocation for P%d--R%d : ",i+1,j+1);
            scanf("%d",&allocation[i][j]);
        }
    }
    for(int i=0;i<num_process;i++)
    {
        for(int j=0;j<num_resources;j++)
        {
            printf("Enter the maximum for P%d--R%d : ",i+1,j+1);
            scanf("%d",&max[i][j]);
        }
    }
    for(int i=0;i<num_resources;i++)
    {
        printf("Enter the available instances in r%d : ",i+1);
        scanf("%d",&available[i]);
    }
    calculateneed();

    printf("Enter the process to have request : ");
    int process_id;
    scanf("%d",&process_id);

    int request[num_resources];
    for(int i=0;i<num_resources;i++)
    {
        printf("Enter the number of request resource for r%d : ",i+1);
        scanf("%d",&request[i]);
    }

    requestresource(process_id-1,request);
}
#include<stdio.h>
#include<stdbool.h>

#define num_process 5
#define num_resources 3

int allocation[num_process][num_resources],max[num_process][num_resources],need[num_process][num_resources];
int available[num_resources];

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

bool dedectdeadlock()
{
    int work[num_resources];
    bool finish[num_process]={false};

    for(int i=0;i<num_resources;i++)
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
                    }
                    count++;
                    found=true;
                    finish[i]=true;
                }
            }
        }

        if(found==false)
        {
            printf("Deadlock dedected\n");
            for(int i=0;i<num_process;i++)
            {
                if(finish[i]==false)
                {
                    printf("p%d cause deadlock\n",i+1);
                }
            }
            return true;
            printf("\n");
        }
    }
    printf("No deadlock dedected\n");
    return true;
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
    dedectdeadlock();

    return 0;
    
}
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys.ipc.h>
#include<sys/shm.h>

int main()
{
    int shm_id=shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT | 0666);
    if(shm_id<0)
    {
        perror("Shared memory creation error");
        exit(1);
    }

    int *shared_mem=(int*)shmat(shm_id,NULL,0);
    if(shared_mem==(int *)-1)
    {
        perror("Failed to attach the shared memeory");
        exit(1);
    }

    *shared_mem=0;
    printf("Initial value of of the shared memory : %d\n",*shared_mem);

    pid_t pid;
    pid=fork();
    if(pid==-1)
    {
        perror("Falied to fork");
        exit(1);
    }

    if(pid==0)
    {
        *shared_mem+=10;
        printf("The shared memory value incremented in child process to : %d\n",*shared_mem);
        shmdt(shared_mem);
        exit(0);
    }
    else
    {
        printf("The shared memory value read by the parent process : %d\n",*shared_mem);
        shmdt(shared_mem);
        shmclt(shm_id,IPC_RMID,NULL);
    }
    return 0;
}
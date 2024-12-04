#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
//#include <sys/wait.h>
int main()
{
    pid_t pid;
    pid=fork();

    if(pid==-1)
    {
        perror("Fork error");
        exit(1);
    }
    if(pid==0)
    {
        printf("Child process : %d\n",getpid());
        exit(0);
    }
    else
    {
        wait(NULL);
        printf("Parent process : %d\n",getpid());
    }

    return 0;
}


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
    pid_t pid;
    pid=fork();

    if(pid==-1)
    {
        perror("Fork failed");
        exit(1);
    }

    if(pid==0)
    {
        printf("the child process(pid %d) is now running and will exit\n",getpid());
        exit(0);
    }
    else
    {
        printf("The parent process(pid %d) is now running and did not wait for child process",getpid());
        printf("The child process should be a zombie now");
        sleep(10);
        printf("The parent process finished executing and now is exiting");
    }
}
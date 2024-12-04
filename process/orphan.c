#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys\types.h>

int main()
{
    pid_t pid =fork();
    if(pid==-1)
    {
        perror("Fork error");
        exit(1);
    }

    if(pid==0)
    {
        printf("The child process(pid - %d) is now running",getpid());
        sleep(5);
        printf("The chid process is a orphan process now");
    }
    else
    {
        printf("The parent process(pid - %d)is running now and will exit",getpid());
        exit(0);
    }
}
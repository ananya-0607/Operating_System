#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>

int main()
{
    int fd[2];
    pid_t pid;
    char message[]="Hello this is the message";
    char buffer[1024];

    if(pipe(fd)<0)
    {
        perror("Pipe not created");
        exit(1);
    }

    pid=fork();
    if(pid==-1)
    {
        perror("Error in fork");
        exit(1);
    }
    
    if(pid==0)
    {
        close(fd[0]);
        ssize_t item=write(fd[1],message,strlen(message)+1);
        close(fd[1]);
        printf("The message written thru child process\n");
    }
    else
    {
        close(fd[1]);
        ssize_t item=read(fd[0],buffer,sizeof(buffer));
        close(fd[0]);
        printf("The message in the buffer : %s\n",buffer);
    }

    return 0;
}
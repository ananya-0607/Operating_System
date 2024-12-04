#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

int main()
{
    int fd=open("file.txt",O_WRONLY | O_CREAT | O_TRUNC,0644 );
    if(fd==-1)
    {
        perror("Open error");
        exit(1);
    }
    const char *text="Hello World\n";
    ssize_t item=write(fd,text,strlen(text));
    if(item==-1)
    {
        perror("Writing Error");
        exit(1);
    }
    else
    {
        printf("Bytes written : %ld",item);
    }
    close(fd);
    return 0;
}
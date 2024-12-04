#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

# define N 5

sem_t chopstick[N];
sem_t mutex;

void *philos(void *num)
{
    int id=*(int *)num;

    while(1)
    {
        printf("Philosopher %d is thinking\n",id);

        sem_wait(&mutex);

        sem_wait(&chopstick[i]);
        sem_wait(&chopstick[(i+1)%N]);

        printf("Philosopher %d is eating\n",id);

        sem_post(&chopstick[i]);
        sem_post(&chopstick[(i+1)%N]);

        printf("Philosopher %d stopped eating and started thinking\n",id);

        sleep(5);
    }

}

int main()
{
    pthread_t phil[N];
    int philosopher_id[N];

    sem_init(&mutex,0,N-1);
    for(int i=0;i<N;i++)
    {
        sem_int(&chopstick[i],0,1);
    }

    for(int i=0;i<N;i++)
    {
        philosopher_id[i]=i;
        pthread_create(&phil[i],NULL,philos,&philosopher_id[i])
    }

    for(int i=0;i<N;i++)
    {
        pthread_join(&phil[i],NULL);
    }

    for(int i=0;i<N;i++)
    {
        sem_destroy(&chopstick[i]);
    }
    sem_destroy(&mutex);

    return 0;

}
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

# define BUFFER_SIZE 10
int buffer[BUFFER_SIZE];
int count=0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void *producer(void *param)
{
    int item;
    for(int i=0;i<5;i++)
    {

        int item=rand()%100;
        sleep(1);

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[count]=item;
        printf("The item produced : %d\n",item);
        count++;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *param)
{
    int item;
    for(int i=0;i<5;i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        count--;
        int item=buffer[count];
        printf("The item consume : %d\n",item);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(1);
    }
}

int main()
{
    pthread_t prod,cons;

    sem_init(&empty,0,BUFFER_SIZE);
    sem_init(&full,0,0);
    pthread_mutex_init(&mutex,NULL);

    pthread_create(&prod,NULL,producer,NULL);
    pthread_create(&cons,NULL,consumer,NULL);

    pthread_join(prod,NULL);
    pthread_join(cons,NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
}
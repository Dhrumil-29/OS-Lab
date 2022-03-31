// Name: Dhrumil Mevada
// ID: 201901128

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

sem_t adone,bdone;

void * evenPrint(void * data)
{
    for(int i=0;i<=100;i+=2)
    {
        sem_wait(&bdone);
        printf("%d \n",i);
        sem_post(&adone);
    }
}
void * oddPrint(void *data)
{
    for(int i=1;i<100;i+=2)
    {
        sem_wait(&adone);
        printf("%d \n",i);
        sem_post(&bdone);
    }
}

int main()
{
    pthread_t t1, t2;

    sem_init(&adone,0,0);
    sem_init(&bdone,0,1);

    pthread_create(&t1, NULL, evenPrint, NULL);
    pthread_create(&t2, NULL, oddPrint, NULL);


    /* wait for all threads */
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}

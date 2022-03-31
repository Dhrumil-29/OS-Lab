// Name: Dhrumil Mevada
// ID: 201901128

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

sem_t aDone,bDone;

void *first(void *data)
{

    printf("First\n");
    sem_post(&aDone);
}
void *second(void *data)
{
    sem_wait(&aDone);
    printf("Second\n");
    sem_post(&bDone);
}
void *third(void *data)
{
    sem_wait(&bDone);
    printf("Third\n");
}
int main()
{
    pthread_t t1, t2, t3;

    sem_init(&aDone,0,0);
    sem_init(&bDone,0,0);

    pthread_create(&t3, NULL, third, NULL);
    pthread_create(&t2, NULL, second, NULL);
    pthread_create(&t1, NULL, first, NULL);


    /* wait for all threads */
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    return 0;
}

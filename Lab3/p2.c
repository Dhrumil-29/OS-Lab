//Name: Yash Sakaria
//ID: 201901165
 
#include <stdio.h>
#include <string.h>
#include <pthread.h> 
#include<semaphore.h>

char *p;

void *solve(void *args)
{
    char *fileName = (char *)args;
    FILE *fp;
    char c;
    fp = fopen(fileName,"r");

    if(fp == NULL)
    {
        return NULL;
    }

    int lineCount = 0;

    for (c = getc(fp); c != EOF; c = getc(fp))
    {
        if (c == '\n')
            lineCount = lineCount + 1;
    }
    printf("%s %d\n", fileName, lineCount);

    return NULL;
}

int main(int n, char *argv[]) 
{
    if(n < 2) 
    {
    	printf("Please enter atleast one file name");
    	return 0;
    }

    pthread_t thread[n-1];

    for(int i=1 ; i<n ; ++i)
    	pthread_create(&thread[i-1], NULL, solve, (void *)argv[i]);
    
    for(int i=1 ; i<n ; i++)
    	pthread_join(thread[i-1], NULL);

    return 0;
}
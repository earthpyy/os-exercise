#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_t thread_id[2];
int counter;
pthread_mutex_t mutex;

void *doThing(void *arg)
{
    unsigned long i = 0;

    pthread_mutex_lock(&mutex);
    counter += 1;
    printf("\n Job %d started\n", counter);

    for (i = 0; i < (0xFFFFFFFF); i++);
    printf("\n Job %d finished\n", counter);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(void)
{
    int i = 0;
    int err;

    pthread_mutex_init(&mutex, NULL);

    while (i < 2)
    {
        err = pthread_create(&(thread_id[i]), NULL, &doThing, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        i++;
        
    }

    pthread_join(thread_id[0], NULL);
    pthread_join(thread_id[1], NULL);
    
    return 0;
}
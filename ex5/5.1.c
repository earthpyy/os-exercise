#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_t thread_id[2];
int counter;

void *doThing(void *arg)
{
    unsigned long i = 0;
    counter += 1;
    printf("\n Job %d started\n", counter);

    for (i = 0; i < (0xFFFFFFFF); i++);
    printf("\n Job %d finished\n", counter);

    return NULL;
}

int main(void)
{
    int i = 0;
    int err;

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
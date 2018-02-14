#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/time.h>

#define N 1000

void *run(void *arg) {
    pthread_exit(0);
    return NULL;
}

int main()
{
    struct timeval tv1, tv2;
    int i;
    pthread_t thread;

    gettimeofday(&tv1, NULL);
    // Start counting...
    for (i = 0; i < N; i++) {
        pthread_create(&thread, NULL, &run, NULL);
        pthread_join(thread, NULL);
    }
    // Stop
    gettimeofday(&tv2, NULL);

    printf ("Total time = %f seconds\n",
        (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
        (double) (tv2.tv_sec - tv1.tv_sec));
}
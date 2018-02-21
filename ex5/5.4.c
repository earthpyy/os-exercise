#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define MATES 5
#define ROUNDMAX 3
#define MILKMIN 3
#define MILKMAX 7

int milk;
int round = 0;

pthread_t thread[MATES];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int myRand(int start, int end)
{
    return (rand() % (end - start + 1)) + start;
}

void drinkMilkAndBuyIfNeed(int id)
{
    // simulate time to drink
    sleep(1);

    // possibility = 0.2 to drink milk
    if (myRand(0, 9) <= 1)
    {
        // lock
        pthread_mutex_lock(&mutex);
        printf("[T%d]\t locked!\n", id);

        // drink milk
        // sleep(1);
        milk--;
        printf("[T%d]\t drinking milk. (%d left)\n", id, milk);

        // check if milk is empty
        if (milk <= 0)
        {
            printf("[T%d]\t milk is empty! buying some...\n", id);
            // go buy some milk (between MILKMIN to MILKMAX)
            // sleep(1);
            milk += myRand(MILKMIN, MILKMAX);
            printf("[T%d]\t done! milk amount is %d.\n", id, milk);

            // update round and send signal to main()
            round++;
            pthread_cond_signal(&cond);
            printf("[T%d]\t sent signal to main()\n", id);
        }
        pthread_mutex_unlock(&mutex);
        printf("[T%d]\t unlocked!\n", id);
    }
    // not drink
    else
    {
        printf("[T%d]\t not drink milk...\n", id);
    }
}

void *entry(void *arg)
{
    int id = (int) arg;

    while (1)
    {
        drinkMilkAndBuyIfNeed(id);
    }

    return NULL;
}

int main()
{
    int i;
    srand(time(NULL));

    // set milk amount to random value between MILKMIN to MILKMAX
    milk = myRand(MILKMIN, MILKMAX);
    printf("[MAIN]\t starting milk amount is %d.\n", milk);

    for (i = 0; i < MATES; i++)
    {
        if (pthread_create(&thread[i], NULL, &entry, (void *) i) != 0)
        {
            printf("Error creating thread %d!\n", i);
        }
    }

    // lock
    pthread_mutex_lock(&mutex);

    while (round < ROUNDMAX)
    {
        printf("[MAIN]\t already bought %d time(s), so go on...\n", round);

        // wait for signal
        pthread_cond_wait(&cond, &mutex);
        printf("[MAIN]\t received signal!\n");
    }

    // for (i = 0; i < MATES; i++)
    // {
    //     pthread_join(thread[i], NULL);
    //     // printf("[MAIN]\t thread %d is completed!\n", i);
    // }

    printf("\n[MAIN]\t COMPLETELY BOUGHT MILK %d TIMES!\n", ROUNDMAX);

    // unlock
    pthread_mutex_unlock(&mutex);
    
    return 0;
}
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>

#define N 10000000

void *print(void *arg) {
    int i = 1;
    while (1) {
        if (i == N) {
            printf(".");
            i = 0;
        }
        i++;
    }
    return NULL;
}

void *waitForInput(void *arg) {
    char temp[256];
    while (1) {
        scanf("%[^\n]", temp);
        getchar();
        printf("Thank you for your input.");
    }
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, &print, NULL);
    waitForInput(NULL);
    return 0;
}
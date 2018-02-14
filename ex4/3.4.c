#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

#define N 3
#define K 4
#define M 3

num A[N][K] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};

num B[K][M] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9},
    {10, 11, 12}
};

#define PRNT "%d\t"
typedef int num;

typedef struct targs {
    int x;
    int y;
    num result;
} targs;

void* multiply(void* arg) {
    targs* tdata = (targs *) arg;
    int x = tdata->x;
    int y = tdata->y;

    int i;
    for (i = 0; i < K; i++) {
        tdata->result += A[x][i] * B[i][y];
    }

    return NULL;
}

num** calculate() {
    targs data[N][M];
    num** ans = (num **) malloc(N * sizeof(num *));
    pthread_t thread[N][M];
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            data[i][j].x = i;
            data[i][j].y = j;
            data[i][j].result = 0;
            pthread_create(&thread[i][j], NULL, &multiply, (void *) &data[i][j]);
        }
    }

    for (i = 0; i < N; i++) {
        ans[i] = (num *) malloc(M * sizeof(num));
        for (j = 0; j < M; j++) {
            pthread_join(thread[i][j], NULL);
            ans[i][j] = data[i][j].result;
        }
    }

    return ans;
}

int main() {
    num **ans = calculate();
    int i, j;
    
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            printf(PRNT, ans[i][j]);
        }
        printf("\n");
    }
    return 0;
}
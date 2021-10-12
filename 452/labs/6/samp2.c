#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* swapper(void*);
int arr[2];

int main() {
    pthread_t who;
    long int loop;

    scanf("%ld", &loop);
    arr[0] = 0;
    arr[1] = 1;
    pthread_create(&who, NULL, swapper, &loop);
    for (int k = 0; k < loop; k++) {
	    int temp = arr[1];
            arr[1] = arr[0];
            arr[0] = temp;

    }
    int rc;
    pthread_join(who, (void **) &rc);
    printf ("Values: %5d %5d\n", arr[0], arr[1]);
}

void* swapper(void *arg) {
    long int *num = (long int *) arg;
    for (int k = 0; k < *num; k++) {
        int temp = arr[1];
            arr[1] = arr[0];
            arr[0] = temp;
    }
    return 0;
}

